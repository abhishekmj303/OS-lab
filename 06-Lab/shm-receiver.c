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
// for ipc
#include <sys/ipc.h>
// for shm
#include <sys/shm.h>

#define SHMSIZE 500

// Basic working:
// 1. All the messages ends with -1
// 2. If end of prev msg is changed to -2, then it means new msg is available
// 3. Read the new msg until -1

int main()
{
    key_t key = 32323;

    int shm_id = shmget(key, SHMSIZE, 0666);
    if (shm_id < 0) // when -1
    {
        printf("Not able to get Shared Memory\n");
        exit(1);
    }

    int* shm = shmat(shm_id, NULL, 0);
    if (shm == (int *) -1)
    {
        printf("Not able to attach Shared Memory\n");
        exit(1);
    }

    printf("Reading Shared Memory: ");
    int * msg1 = shm;
    while (*msg1 != -1) // read until end of msg
    {
        printf("%d ", *msg1);
        msg1++;
    }
    printf("\n");

    
    printf("Writing into Shared Memory\n");
    int *msg2 = msg1 + sizeof(int);
    for (int i = 25; i < 50; i++)
    {
        *msg2 = i;
        msg2++;
    }
    *msg2 = -1; // End of msg 2

    *msg1 = -2; // Change end of received msg from -1 to -2

    return 0;
}