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
    // execl()
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        execl("/bin/echo", "echo", "Hello in execl()", NULL);
    }
    else if (pid1 < 0)
    {
        printf("Not able to create child process\n");
    }

    // execv()
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        char *args[] = {"echo", "Hello in execv()", NULL};
        execv("/bin/echo", args);
    }
    else if (pid2 < 0)
    {
        printf("Not able to create child process\n");
    }

    // execle()
    pid_t pid3 = fork();
    if (pid3 == 0)
    {
        char *env[] = {"NAME=Abhishek", NULL};
        execle("/bin/echo", "echo", "Hello, Abhishek in execle()", NULL, env);
    }
    else if (pid3 < 0)
    {
        printf("Not able to create child process\n");
    }

    // execve()
    pid_t pid4 = fork();
    if (pid4 == 0)
    {
        char *args[] = {"echo", "Hello, Abhishek in execve()", NULL};
        char *env[] = {"NAME=Abhishek", NULL};
        execve("/bin/echo", args, env);
    }
    else if (pid4 < 0)
    {
        printf("Not able to create child process\n");
    }

    // execlp()
    pid_t pid5 = fork();
    if (pid5 == 0)
    {
        execlp("echo", "echo", "Hello in execlp()", NULL);
    }
    else if (pid5 < 0)
    {
        printf("Not able to create child process\n");
    }

    // execvp()
    pid_t pid6 = fork();
    if (pid6 == 0)
    {
        char *args[] = {"echo", "Hello in execvp()", NULL};
        execvp("echo", args);
    }
    else if (pid6 < 0)
    {
        printf("Not able to create child process\n");
    }

    int wait_pid;
    int status;

    // wait(NULL)
    wait_pid = wait(NULL);
    printf("Used wait(NULL) returned, pid: %d\n", wait_pid);

    // wait(&status)
    wait_pid = wait(&status);
    printf("Used wait(&status) returned, pid: %d, with status: %d\n", wait_pid, status);

    // waitpid()
    waitpid(pid3, NULL, 0);
    printf("Used waitpid() for pid: %d\n", pid3);

    // waitpid()
    waitpid(pid4, &status, 0);
    printf("Used waitpid() with &status for pid: %d, with status: %d\n", pid4, status);

    // not waiting for other 2 processes
    printf("Not waiting for other 2 processes\n");

    return 0;
}