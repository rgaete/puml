extern int arr[11];

int total()
{
  int i=0, sum=0;
  while(arr[i+1]!='\0')
  {
    sum=sum+arr[i];
    i++;
  }
  i=0;
  printf("The sum is: ");
  printf("%d, \n", sum);
  return sum;
}

int average(int sum)
{
   int ave=0;
   ave=sum/10;
   printf("the average is: ");
   printf("%d \n", ave);
}

