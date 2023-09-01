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
    pid_t pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 < 0)
    {
        printf("Not able to create child process\n");
        exit(0);
    }
    else if (pid1 == 0) // child 1
    {
        printf("Child 1 My id is %d and my parent id is %d\n", pid1, getppid());
    }
    else // parent
    {
        pid2 = fork();
        if (pid2 < 0)
        {
            printf("Not able to create child process\n");
            exit(0);
        }
        else if (pid2 == 0) // child 2
        {
            pid3 = fork();
            if (pid3 < 0)
            {
                printf("Not able to create child process\n");
                exit(0);
            }
            else if (pid3 == 0) // child 3
            {
                printf("Child 3 My id is %d and my parent id is %d\n", pid3, getppid());
            }
            else // child 2
            {
                pid4 = fork();
                if (pid4 < 0)
                {
                    printf("Not able to create child process\n");
                    exit(0);
                }
                else if (pid4 == 0) // child 4
                {
                    printf("Child 4 My id is %d and my parent id is %d\n", pid4, getppid());
                }
                else // child 2
                {
                    wait(NULL);
                    wait(NULL);
                    printf("Child 2 My id is %d and my parent id is %d\n", pid2, getppid());
                }
            }
        }
        else // parent
        {
            waitpid(pid2, NULL, 0);
            printf("Parent Process My id is %d and my parent id is %d\n", getpid(), getppid());
        }
    }

    return 0;
}