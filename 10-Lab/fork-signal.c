// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define SIZE 8

void sig_handler(int signal)
{
    printf("Division by zero not possible\n");
    // exit(1);
    // raise(SIGKILL);
}

int main()
{
    signal(SIGFPE, sig_handler);

    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("Not able to create child process\n");
        exit(1);
    }
    else if (pid == 0) // child process
    {
        int random = 0;
        srand(time(NULL));
        printf("\nChild process, Random:\n");
        while (1)
        {
            random = rand() %21 +10;
            printf("%d\n", random);
            if (random > 20)
                exit(0);
        }
    }
    else // parent process
    {
        wait(NULL);
        int num;
        printf("\nEnter a number: ");
        scanf("%d", &num);

        int arr[SIZE] = {2, 1, 3, 0, 5, 0, 7, 9};
        printf("Array: ");
        for (int i = 0; i < SIZE; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");

        int rem;
        printf("\nRemainders: \n");
        for (int i = 0; i < SIZE; i++)
        {
            if (arr[i] == 0)
                raise(SIGFPE);
            else
            {
                rem = num % arr[i];
                printf("%d %% %d = %d\n", num, arr[i], rem);
            }
        }
    }

    return 0;
}