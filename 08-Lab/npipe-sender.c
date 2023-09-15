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
// for named pipe
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
    int fd1; // file descriptor for fifo file
    char * fifo_path = "/tmp/myfifo2018"; // path to store fifo file

    if (mkfifo(fifo_path, 0666) == -1) // create fifo file
    {
        printf("Not able to create fifo file\n");
        return 1;
    }

    int A; // integer to send
    printf("Enter an integer A: ");
    scanf("%d", &A);

    printf("Writing A to fifo file...\n");

    // open fifo file as write-only
    fd1 = open(fifo_path, O_WRONLY);
    if (fd1 == -1)
    {
        printf("Not able to open fifo file as write-only\n");
        return 1;
    }

    // write A into fifo file
    if (write(fd1, &A, sizeof(A)) == -1)
    {
        printf("Not able to write into fifo file\n");
        return 1;
    }

    close(fd1); // close fifo file

    int B;

    // open fifo file as read-only
    fd1 = open(fifo_path, O_RDONLY);
    if (fd1 == -1)
    {
        printf("Not able to open fifo file as read-only\n");
        return 1;
    }

    // read 1's complement of A from fifo file
    if (read(fd1, &B, sizeof(B)) == -1)
    {
        printf("Not able to read from fifo file\n");
        return 1;
    }

    printf("Value of B read (1's Complement of A): %d\n", B);
    close(fd1); // close fifo file

    unlink(fifo_path); // remove fifo file
}