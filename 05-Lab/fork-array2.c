#include <stdio.h>
// for fork
#include <unistd.h>
// for wait
#include <sys/wait.h>
// for exit, malloc
#include <stdlib.h>
// for pid_t
#include <sys/types.h>

void printArray(int *arr, int n)
{
    printf("Array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("\tat %p -> %d\n", &arr[i], arr[i]);
    }
}

void inputArray(int *arr, int n)
{
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
}

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // parent process
        wait(NULL);

        printf("\nParent process\n");

        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int *arr1 = (int *)malloc(n * sizeof(int));
        inputArray(arr1, n);

        printArray(arr1, n);

        printf("Sorted ");
        for (int i = 0; i < n; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if (arr1[j] < arr1[i])
                {
                    int temp = arr1[i];
                    arr1[i] = arr1[j];
                    arr1[j] = temp;
                }
            }
        }
        printArray(arr1, n);
        free(arr1);
    }
    else if (pid == 0)
    {
        // child process
        printf("\nChild process\n");

        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int *arr2 = (int *)malloc(n * sizeof(int));
        inputArray(arr2, n);

        printArray(arr2, n);

        printf("Reverse ");
        for (int i = 0; i < n/2; i++)
        {
            int temp = arr2[i];
            arr2[i] = arr2[n-i-1];
            arr2[n-i-1] = temp;
        }
        printArray(arr2, n);
        free(arr2);
    }
    else
    {
        printf("Not able to create child process\n");
    }

    return 0;
}