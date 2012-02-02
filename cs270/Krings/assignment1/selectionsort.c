extern int arr[1000];
extern int LENGTH;

int selectionsort()
{
  int temp,i,j,first;
  for(i=LENGTH-1;i>0;i--)
    {
      first=0;
      for(j=1;j<=i;j++)
	{
	  if(arr[j]<arr[first])
	    {
	      first=j;
	    }
	}
      swap(i,first);
    }
  return 0;
}
