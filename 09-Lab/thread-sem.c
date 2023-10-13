// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t A, B;

void *funA()
{
    sem_wait(&A);
    printf("A1\n");
    sem_post(&B);

    sleep(0.1);

    sem_wait(&A);
    printf("A2\n");
    sem_post(&B);
}

void *funB()
{
    sem_wait(&B);
    printf("B1\n");
    sem_post(&A);

    sleep(0.1);

    sem_wait(&B);
    printf("B2\n");
    sem_post(&A);
}

int main()
{
    pthread_t tA, tB;

    sem_init(&A, 0, 1);
    sem_init(&B, 0, 1);

    if (
        pthread_create(&tA, NULL, &funA, NULL) != 0
        || pthread_create(&tB, NULL, &funB, NULL) != 0
    )
    {
        printf("Not able to create thread\n");
        exit(1);
    }

    if (
        pthread_join(tA, NULL) != 0
        || pthread_join(tB, NULL) != 0
    )
    {
        printf("Not able to join thread\n");
        exit(0);
    }

    return 0;
}