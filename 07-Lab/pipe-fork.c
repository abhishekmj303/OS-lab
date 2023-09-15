// Abhishek M J
// CS21B2018

#include <stdio.h>
// for fork
#include <unistd.h>
// for wait
#include <sys/wait.h>
// for exit, malloc
#include <stdlib.h>
// for pid_t
#include <sys/types.h>

int main()
{
    int pipe1[2], pipe2[2];
    if(pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        printf("Not able to create pipe\n");
        exit(1);
    }

    // pipe[0] -> read, pipe[1] -> write
    // pipe1: parent(w) -> child(r)
    // pipe2: child(w) -> parent(r)
    
    int n;
    printf("(pid: %d) Enter the length of string: ", getpid());
    scanf("%d", &n);

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("Not able to create child process\n");
        exit(1);
    }
    else if (pid == 0) // child process
    {
        close(pipe1[1]); // write end
        close(pipe2[0]); // read end

        char str[n];
        read(pipe1[0], str, sizeof(str));
        printf("(pid: %d) String received from parent: %s\n", getpid(), str);

        for (int i = 0; i < n/2; i++)
        {
            char temp = str[i];
            str[i] = str[n-i-1];
            str[n-i-1] = temp;
        }

        write(pipe2[1], str, sizeof(str));

        exit(0);
    }
    // parent process

    close(pipe1[0]); // read end
    close(pipe2[1]); // write end

    char str[n];
    printf("(pid: %d) Enter the string: ", getpid());
    scanf("%s", str);

    write(pipe1[1], str, sizeof(str));
    
    char rev_str[n];
    read(pipe2[0], rev_str, sizeof(rev_str));

    wait(NULL);

    printf("(pid: %d) Reversed string received from child: %s\n", getpid(), rev_str);

    return 0;
}