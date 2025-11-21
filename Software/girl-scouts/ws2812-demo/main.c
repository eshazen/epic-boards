/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[3];
struct cRGB temp;

#define BRITE 100

int main(void)
{
  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #endif

  // initialize the array
  led[0].r=BRITE; led[0].g=0; led[0].b=0; 
  led[1].r=BRITE; led[1].g=BRITE; led[1].b=0; 
  led[2].r=0; led[2].g=BRITE; led[2].b=0; 

  while(1)
  {
    ws2812_setleds(led,3);

    // roll the colors
    temp = led[0];
    led[0] = led[1];
    led[1] = led[2];
    led[2] = temp;

    _delay_ms(500);
  }
}
