#include <stdio.h>
// for fork
#include <unistd.h>
// for wait
#include <sys/wait.h>
// for exit
#include <stdlib.h>
// for pid_t
#include <sys/types.h>

void updateArray(int *arr, int n, int num)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] += num;
    }
}

void printArray(int *arr, int n)
{
    printf("Array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\tat %p -> %d\n", &arr[i], arr[i]);
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid > 0)
    {
        // parent
        printf("\nIn parent process, update array by subtracting 3\n");
        updateArray(arr, n, -3);
        printArray(arr, n);

        int min_num = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] < min_num)
            {
                min_num = arr[i];
            }
        }
        printf("Minimum element after update: %d\n", min_num);

        printf("Process id: %d; Parent process id: %d\n", getpid(), getppid());

        wait(NULL);
    }
    else if (pid == 0)
    {
        // child
        printf("\nIn child process, update array by adding 2\n");
        updateArray(arr, n, 2);
        printArray(arr, n);

        int max_num = arr[0];
        for (int i = 1; i < n; i++)
        {
            if (arr[i] > max_num)
            {
                max_num = arr[i];
            }
        }
        printf("Maximum element after update: %d\n", max_num);

        printf("Process id: %d; Parent process id: %d\n", getpid(), getppid());
    }
    else
    {
        printf("Not able to create child process\n");
    }


    return 0;
}