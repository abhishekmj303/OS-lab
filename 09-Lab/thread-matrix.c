// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

#define n 3
#define m 3

int M1[n][m] = {
    {1, 2, 3},
    {3, 2, 1},
    {5, 6, 2}
};
int M2[n][m] = {
    {3, 2, 1},
    {1, 2, 3},
    {2, 6, 5}
};

void printMatrix(int mat[n][m])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void *add(void *arg)
{
    int *A = arg;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(A + i*n + j) = M1[i][j] + M2[i][j];

    return NULL;
}

void *subtract(void *arg)
{
    int *A = arg;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            *(A + i*n + j) = M1[i][j] - M2[i][j];

    return NULL;
}

void *multiply(void *arg)
{
    int *A = arg;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            *(A + i*n + j) = 0;
            for (int k = 0; k < m; k++)
                *(A + i*n + j) += M1[i][k] * M2[k][j];
        }

    return NULL;
}



int main()
{
    int A[n][m];
    int S[n][m];
    int M[n][m];

    pthread_t t1, t2, t3;

    if (
        pthread_create(&t1, NULL, &add, A) != 0
        || pthread_create(&t2, NULL, &subtract, S) != 0
        || pthread_create(&t3, NULL, &multiply, M) != 0
    )
    {
        printf("Not able to create thread\n");
        exit(1);
    }

    if (pthread_join(t1, NULL) != 0 || pthread_join(t2, NULL) != 0)
    {
        printf("Not able to join thread\n");
        exit(0);
    }

    printf("A = M1 + M2:\n");
    printMatrix(A);
    printf("S = M1 - M2:\n");
    printMatrix(S);
    printf("M = M1 @ M2:\n");
    printMatrix(M);

    return 0;
}