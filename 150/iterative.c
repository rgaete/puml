#include <stdio.h>

int Factorial(long int i);
void IntToAscii(int num);

int main() 
{ 
  long int x; 
  x = Factorial(20); 
  printf("%d\n", x);  /*prints factorial*/
  IntToAscii(929292);
} 

int Factorial(long int i) 
{  
  long int result=i;
  while(i!=1)      /*till it reaches 2 of factorial*/
  {
	result=result*(--i);  /*iterate through factorial*/
  }
  return result;    /*return factorial of number*/
}

void IntToAscii(int num) 
{ 
  int prefix, currDigit;  
  if (num < 10) 
  {
    putchar(num + '0');/* print single char */ 
  }
  else 
  { 
    prefix = num / 10; /* shift right one digit */ 
    IntToAscii(prefix); /* print shifted num */ 
    currDigit = num % 10; 
    putchar(currDigit + '0'); /* print shifted digit */ 
  } 
}
