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

int dec2bin(int n, int * bin_arr)
{
    int i = 0;
    while (n > 0)
    {
        bin_arr[i] = n % 2;
        n /= 2;
        i++;
    }
    return i;
}

void ones_complement(int * bin_arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        bin_arr[i] = !bin_arr[i];
    }
}

int bin2dec(int * bin_arr, int n)
{
    int dec = 0;
    for (int i = 0; i < n; i++)
    {
        dec += bin_arr[i] * (1 << i);
    }
    return dec;
}

int main()
{
    int fd1; // file descriptor for fifo file
    char * fifo_path = "/tmp/myfifo2018"; // path to store fifo file

    int A;

    printf("Reading A from fifo file...\n");

    fd1 = open(fifo_path, O_RDONLY); // open fifo file as read-only
    if (fd1 == -1)
    {
        printf("Not able to open fifo file as read-only\n");
        return 1;
    }

    // read A from fifo file
    if (read(fd1, &A, sizeof(A)) == -1)
    {
        printf("Not able to read from fifo file\n");
        return 1;
    }

    printf("Value of A read: %d\n", A);
    close(fd1); // close fifo file

    // 1's complement of A
    int B;
    int bin_arr[32];
    int bin_len = dec2bin(A, bin_arr);
    ones_complement(bin_arr, bin_len);
    B = bin2dec(bin_arr, bin_len);
    printf("1's Complement of A: %d\n", B);

    printf("Writing 1's complement of A to fifo file...\n");

    // open fifo file as write-only
    fd1 = open(fifo_path, O_WRONLY);
    if (fd1 == -1)
    {
        printf("Not able to open fifo file as write-only\n");
        return 1;
    }

    // write B into fifo file
    if (write(fd1, &B, sizeof(B)) == -1)
    {
        printf("Not able to write into fifo file\n");
        return 1;
    }
    
    close(fd1); // close fifo file
}