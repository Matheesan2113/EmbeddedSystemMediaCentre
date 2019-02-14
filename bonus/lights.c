#include <stdio.h>

int main()
{
  unsigned char * Switches;
  unsigned char * LEDs;
  
  Switches = (unsigned char *)0x0008810;
  LEDs = (unsigned char *)0x0008800;
  
  printf("Beginning.\n");
  
  while(1){
    *LEDs = *Switches;
  }

  return 0;
}
