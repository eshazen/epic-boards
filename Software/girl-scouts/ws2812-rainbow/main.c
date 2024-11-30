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

// generated table of RGB values
#include "rgb32.h"

struct cRGB led[3];
struct cRGB temp;

#define BRITE 100

int main(void)
{
  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #endif

  while( 1) {
    // cycle through rainbow
    for( uint8_t i=0; i<NUM_RGB_COLORS; i++) {

      uint8_t i1 = ((i+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);
      uint8_t i2 = ((i1+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);	

      led[0].g = rgb[i].r;
      led[0].r = rgb[i].g;
      led[0].b = rgb[i].b;

      led[1].g = rgb[i1].r;
      led[1].r = rgb[i1].g;
      led[1].b = rgb[i1].b;

      led[2].g = rgb[i2].r;
      led[2].r = rgb[i2].g;
      led[2].b = rgb[i2].b;

      ws2812_setleds(led,3);
      _delay_ms(25);
    }
  }
}
