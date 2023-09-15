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
    msgid = msgget((key_t) KEY, 0666|IPC_CREAT); // create or get msg-queue
    if (msgid == -1)
    {
        printf("Not able to create Msg Queue\n");
        return 1;
    }

    msg_t my_msg; // msg struct to send

    int n = 10;
    printf("Enter %d numbers: ", n);
    my_msg.arr[0] = n; // set number of elements in arr
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &my_msg.arr[i]); // store numbers in msg_arr
    }

    my_msg.type = 3; // set msg_type

    // sending into msg-queue
    if (msgsnd(msgid, (void *) &my_msg, sizeof(int)*MAX_LEN, 0) == -1)
    {
        printf("Not able to send message from sender\n");
    }

    printf("Sent messsage to receiver\n");

    return 0;
}