
extern int arr[1000];
extern int LENGTH;

int quicksort(int left, int right)
{
  int middle;
  if(left<right)
    {
      middle=partition(left, right);
      quicksort(left, middle);
      quicksort(middle+1, right);
    }
  return 0;
}

int partition(int left, int right)
{
  int x=arr[left];
  int i= left-1;
  int k= right +1;
  int temp;
          do
	    {
	      do
		{
	       	  k--;
	       	}while(x>arr[k]);
                do
	        {
	          i++;
	       	}while(x<arr[i]);
	        if(i<k)
		{
		  swap(i,k);
       		}
	     }while(i<k);
  return k;

}


