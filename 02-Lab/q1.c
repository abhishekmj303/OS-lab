#include <stdio.h>

int main()
{
    FILE *fin = fopen("Input1.txt", "r");
    if (fin == NULL)
    {
        printf("Not able to open file\n");
        return 1;
    }
    
    FILE *fout = fopen("Output1.txt", "w");
    
    printf("File converted:\n");
    char c = fgetc(fin);
    while (c != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            c = c - 32;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c = c + 32;
        }
        
        fputc(c, fout);
        printf("%c", c);
        
        c = fgetc(fin);
    }
    
    fclose(fin);
    fclose(fout);

    
    return 0;
}