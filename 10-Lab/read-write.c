// Abhishek M J
// CS21B2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <time.h>

#define MAX_READERS 5

int readcount = 0;
sem_t wrt, mutex;


void *writer(void *args)
{
    int w_i = (long int) args;

    for (int i = 0; i < 5; i++)
    {
        sleep(rand()%2+1);
        sem_wait(&wrt);
        printf("Writer %d is writing...\n", w_i);
        sem_post(&wrt);
    }

    return NULL;
}

void *reader(void *args)
{
    int r_i = (long int) args;

    for (int i = 0; i < 5; i++)
    {
        sleep(rand()%5+0);
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
        {
            sem_wait(&wrt);
            printf("readcount = 1\n");
        }
        sem_post(&mutex);

        printf("Reader %d is reading...\n", r_i);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
        {
            sem_post(&wrt);
            printf("readcount = 0\n");
        }
        sem_post(&mutex);
    }
    
    return NULL;
}


int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    srand(time(NULL));

    pthread_t wrt_thread, rdr_threads[MAX_READERS];

    for (long int i = 0; i < MAX_READERS; i++)
    {
        if (pthread_create(&rdr_threads[i], NULL, &reader, (void *)i) != 0)
        {
            printf("Not able to create thread\n");
            exit(1);
        }
    }
    if (pthread_create(&wrt_thread, NULL, &writer, (void *)0) != 0)
    {
        printf("Not able to create thread\n");
        exit(1);
    }

    if (pthread_join(wrt_thread, NULL) != 0)
    {
        printf("Not able to join thread\n");
        exit(0);
    }
    for (int i = 0; i < MAX_READERS; i++)
    {
        if (pthread_join(rdr_threads[i], NULL) != 0)
        {
            printf("Not able to create thread\n");
            exit(1);
        }
    }


    return 0;
}