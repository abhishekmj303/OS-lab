#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

typedef struct {
    int n;
    int m;
    int sum;
} args_t;

void *sum_n_to_m(void *args)
{
    args_t *temp = args;
    temp->sum = 0;
    for (int i = temp->n; i <= temp->m; i++)
        temp->sum += i;
    return NULL; 
}

int main()
{
    pthread_t threads[5];
    args_t args[5];

    int n = 1000, t = 5;
    int div = n/t;
    for (int i = 0; i < t; i++)
    {
        args[i].n = div * i + 1;
        args[i].m = args[i].n-1 + div;
        if (pthread_create(&threads[i], NULL, &sum_n_to_m, (void *)&args[i]) != 0)
        {
            printf("Not able to create thread\n");
            exit(1);
        }
    }

    int sum = 0;
    for (int i = 0; i < t; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("Not able to join thread\n");
            exit(0);
        }
        sum += args[i].sum;
    }

    printf("Sum of first %d numbers: %d\n", n, sum);

    return 0;
}