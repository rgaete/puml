#include<stdio.h>

int main()
{
        while(1)
        {
                FILE *file=fopen("stuff.txt", "a");
                fprintf(file, "k");
                fclose(file);
        }
}

