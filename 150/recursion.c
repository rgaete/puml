#include <stdio.h>

int Factorial(long int i);
void IntToAscii(int num);

int main() 
{ 
  long int x; 
  x = Factorial(20); 
  printf("%d\n", x);
  IntToAscii(929292);
} 

int Factorial(long int n) 
{ 
  if (n < 2)
  return n; 
  return (n * Factorial(n-1)); 
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
