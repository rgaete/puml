int maximum()
{
int max=arr[0], i=1;
  while(arr[i]!='\0')
  {
     if(arr[i]>=max)
     {
       max=arr[i];
     }
     i++;
  }
  printf("The maximum is: ");
  printf("%d", max);

}

