// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <time.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;

sem_t empty, full;
sem_t mutex;

int shift_buffer()
{
    for (int i = 0; i < SIZE - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
}

int produce_item()
{
    sleep(rand()%2+1);
    return rand() %100;
}

void consume_item(int item)
{
    sleep(rand()%5+1);
    printf("Consumed item: %d\n", item);
}

void *producer()
{
    int item;
    for (int i = 0; i < 10; i++)
    {
        item = produce_item();

        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[count++] = item;
        printf("Produced item: %d\n", buffer[count-1]);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer()
{
    int item;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[0];
        shift_buffer();
        count--;
        sem_post(&mutex);
        sem_post(&empty);

        consume_item(item);
    }
}


int main()
{
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    srand(time(NULL));

    pthread_t prod, cons;

    if (
        pthread_create(&prod, NULL, &producer, NULL) != 0
        || pthread_create(&cons, NULL, &consumer, NULL) != 0
    )
    {
        printf("Not able to create thread\n");
        exit(1);
    }

    if (
        pthread_join(prod, NULL) != 0
        || pthread_join(cons, NULL) != 0
    )
    {
        printf("Not able to join thread\n");
        exit(0);
    }

    return 0;
}