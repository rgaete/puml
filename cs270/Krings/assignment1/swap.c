extern int arr[];

int swap(swap_1,swap_2)
{
  int *bufp0 = &arr[swap_1];
  int *bufp1;
  int temp;
  bufp1 = &arr[swap_2];
  temp = *bufp0;
  *bufp0 = *bufp1;
  *bufp1 = temp;
}
