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
// for msg-passing
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_LEN 256
#define KEY 21334

typedef struct {
    long int type; // msg_type required in receiver
    int arr[MAX_LEN]; // actual msg_data read in receiver
} msg_t;


int main()
{
    int msgid;
    msgid = msgget((key_t) KEY, 0644); // get msg-queue with KEY
    if (msgid == -1)
    {
        printf("Not able to get Msg Queue\n");
        return 1;
    }

    msg_t my_msg;
    my_msg.type = 3; // set msg_type to receive

    // receive message from sender of msg_type into my_msg struct
    if (msgrcv(msgid, (void *) &my_msg, sizeof(int)*MAX_LEN, my_msg.type, 0) == -1)
    {
        printf("Not able to receive message from sender\n");
        return 1;
    }

    int count = 0;
    printf("Odd numbers received: ");
    int n = my_msg.arr[0]; // get number of integers in array
    for (int i = 1; i <= n; i++)
    {
        if (my_msg.arr[i] %2 == 1) // check for odd
        {
            printf("%d ", my_msg.arr[i]);
            count++;
        }
    }
    printf("\n");

    printf("Total Odd Numbers: %d\n", count);

    msgctl(msgid, IPC_RMID, 0); // remove msg-queue

    return 0;
}