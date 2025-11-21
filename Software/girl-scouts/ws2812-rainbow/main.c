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
#include <avr/pgmspace.h>
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
    for( int i=0; i<NUM_RGB_COLORS; i++) {

      int i1 = ((i+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);
      int i2 = ((i1+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);	

      led[0].r = pgm_read_byte(&(rgb[i][0]));
      led[0].g = pgm_read_byte(&(rgb[i][1]));
      led[0].b = pgm_read_byte(&(rgb[i][2]));

      led[1].r = pgm_read_byte(&(rgb[i1][0]));
      led[1].g = pgm_read_byte(&(rgb[i1][1]));
      led[1].b = pgm_read_byte(&(rgb[i1][2]));

      led[2].r = pgm_read_byte(&(rgb[i2][0]));
      led[2].g = pgm_read_byte(&(rgb[i2][1]));
      led[2].b = pgm_read_byte(&(rgb[i2][2]));

      ws2812_setleds(led,3);
      _delay_ms(100);
    }
  }
}
