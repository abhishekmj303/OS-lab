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
    pid_t pid = fork();

    if (pid > 0)
    {
        // parent process
        printf("\nParent process\n");
        
        printf("Abhishek M J - CS21B2018\n");
        printf("IIITDM Kancheepuram\n");

        printf("Process id: %d, Parent Process id: %d, fork() returned: %d\n", getpid(), getppid(), pid);
    }
    else if (pid == 0)
    {
        printf("\nChild process\n");
        printf("Process id: %d, Parent Process id: %d, fork() returned: %d\n", getpid(), getppid(), pid);

        char *filepath = "./program32";
        execl(filepath, filepath, NULL);

        printf("Ran after Program32 inside Program31\n");
    }
    else
    {
        printf("Not able to create child process\n");
    }
    return 0;
}