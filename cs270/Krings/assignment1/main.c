#include <stdio.h>
#include <stdlib.h>
#include "quicksort.c"
#include "bubblesort.c"
#include "selectionsort.c"
#include "swap.c"

int bubble();
int selectionsort();
int quicksort(int left, int right);
int partition(int left, int right);
int swap(int swap_1, int swap_2);

int arr[1000];
int LENGTH=0;

int main()
{
  char ch;
  int flag=1, k=0, num, p=0, i;
  while(flag!=EOF)                       /*reading until end of input*/
  {
    printf("%s", "Enter numbers to sort. When finished press CTRL+D>");
    
    flag=scanf("%[^0-9]c", &ch);         /*filter anything except a number */  
    flag=scanf("%d", &arr[LENGTH]);      /*store number in int array*/ 
    LENGTH++;
    if(LENGTH>=1000)                     /*if over 1000 characters, then exit*/
      {
          printf("%s", "\nToo many numbers. Can only sort 1000 ints");
	  exit(1);
      }
  }
    bubble();
    quicksort(0, LENGTH);
    selectionsort();
    for(i=0;i<=LENGTH-2;i++)
      {
	printf("\n%d\n", arr[i]);
      }
}
