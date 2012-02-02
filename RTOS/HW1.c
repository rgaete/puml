#include "lightUp.h"

int main()
{  

  DDRB = 0x01;
  DDRA = 0xfe;

  lightUp();    
}
