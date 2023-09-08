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
#include <string.h>

#define MAXLEN 100

int main()
{
    // pipe[0] -> read, pipe[1] -> write
    int pipe1[2]; // pipe1: parent(w) -> child(r)
    if(pipe(pipe1) == -1)
    {
        printf("Not able to create pipe\n");
        exit(1);
    }

    pid_t pid_c;
    pid_c = fork();
    if (pid_c < 0)
    {
        printf("Not able to create child process\n");
        exit(1);
    }
    else if (pid_c == 0) // child process
    {
        close(pipe1[1]); // p-c write end
        char str_p[MAXLEN];
        read(pipe1[0], str_p, sizeof(str_p));
        printf("(Child pid: %d ppid: %d) Message received from parent: %s\n", getpid(), getppid(), str_p);

        int pipe2[2]; // pipe2: grandchild(w) -> child(r)
        if(pipe(pipe2) == -1)
        {
            printf("Not able to create pipe\n");
            exit(1);
        }

        pid_t pid_gc;
        pid_gc = fork();
        if (pid_gc < 0)
        {
            printf("Not able to create grand child process\n");
            exit(1);
        }
        else if (pid_gc == 0) // grandchild process
        {
            close(pipe2[0]); // c-gc read end

            char str_gc[MAXLEN];
            printf("(Grandchild pid: %d ppid: %d) Enter a string: ", getpid(), getppid());
            fgets(str_gc, MAXLEN, stdin);

            write(pipe2[1], str_gc, sizeof(str_gc));

            exit(0);
        }

        close(pipe2[1]); // c-gc write end
        char str_gc[MAXLEN];
        read(pipe2[0], str_gc, sizeof(str_gc));
        printf("(Child pid: %d ppid: %d) Message received from grandchild: %s\n", getpid(), getppid(), str_gc);

        int strd_diff = abs(strlen(str_p) - strlen(str_gc));

        printf("(Child pid: %d ppid: %d) Difference in length of messages: %d\n", getpid(), getppid(), strd_diff);

        exit(0);
    }
    // parent process

    close(pipe1[0]); // read end

    char str_p[MAXLEN];
    printf("(Parent pid: %d ppid: %d) Enter a string: ", getpid(), getppid());
    fgets(str_p, MAXLEN, stdin);

    write(pipe1[1], str_p, sizeof(str_p));

    wait(NULL);

    return 0;
}