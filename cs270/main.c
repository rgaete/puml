#include <stdio.h>
#include "ave.h"
#include "min.h"
#include "max.h"
int arr[11];

int main()
{
   int i, sum=0;;
   printf("Enter 10 numbers>");
   for(i=0;i<=10;i++)
   {
     scanf("%d", &arr[i]);
   }
   arr[11]='\0';
   sum=total();
   average(sum);
   minimum();
   maximum();
}
