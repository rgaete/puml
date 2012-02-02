extern int arr[1000];

int bubble()
{
  int i, k, true=1, temp;
	for(i=0;(i<=LENGTH) && true;i++)
	{
		true=0;
		for(k=0;k<(LENGTH-1);k++)
		{
			if(arr[k+1]>=arr[k])
			{
			  swap(k,k+1);
			  true=1;
			}
		}
	}
	return 0;
}

