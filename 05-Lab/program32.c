#include <stdio.h>

int main()
{
    printf("This is Program32.c\n");
    printf("Array of 4 elements inside Program32: ");
    int arr[4] = {3, 4, 2, 1};
    for (int i = 0; i < 4; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}