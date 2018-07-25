#define FALSE 0
#define TRUE 1

#include "Arduino.h"


int main()
{
	delay_init();
//Arduino Style Handler ----------------------------------------------------	
  setup();
  while (1)
  {
    loop();
  }
//--------------------------------------------------------------------------
}

