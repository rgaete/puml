#include "lightUp.h"

int i;

void delay(unsigned int dly)
{
        for(i=dly; i!=0; i--);
}

void lightUp()
{
  unsigned int time=0;
  while(1)
  {
          PORTB=1;
          time=0;
          while(PINA==0)
          {
                time++;
          }
          if(time>0)
          {
                delay(65000U);  //wait ~second
                PORTB=0;
                delay(time);
          }
  }
}

