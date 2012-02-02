int minimum()
{
  int min=arr[0], i=1;
  while(arr[i]!='\0')
  {
     if(arr[i]<=min)
     {
       min=arr[i];
     }  
     i++;
  }
  printf("The minimum is: ");
  printf("%d", min);
}

