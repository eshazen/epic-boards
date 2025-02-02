/*
 * Girl scout working firmware
 * Go to sleep, wake on button press and select a demo pattern to run for a few secs
 *
 * This example is configured for a ATtiny85 with PLL clock fuse set and
 * the WS2812 string connected to PB4.
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"
#include <string.h>
#include <stdlib.h>
#include "wake.h"

// generated table of RGB values
#include "rgb32.h"

#define max(a,b) ((a)>(b)?(a):(b))
#define max3(a, b, c) ((a>b)?((a>c)?a:c):((b>c)?b:c))

struct cRGB led[3];
struct cRGB temp;

#define BRITE 100

//
// display options
//
#define NUM_OPTIONS 9
void rainbow();
void flicker();
void flash();
void fade( uint8_t r, uint8_t g, uint8_t b);

// needed but not used
ISR(PCINT0_vect) {
  if( !(PINB & _BV(0)))
    button = (button + 1) % NUM_OPTIONS;
  if( !(PINB & _BV(1)))
    button = (button - 1) % NUM_OPTIONS;
}


void all_off() {
  memset( led, 0, sizeof(led));
    ws2812_setleds(led,3);
}


void delay_10ms( int n) {
  for( int i=0; i<n; i++)
    _delay_ms(10);
}



int main(void)
{
  #ifdef __AVR_ATtiny10__
  CCP=0xD8;		// configuration change protection, write signature
  CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
  #endif

  // pull-up on buttons
  PORTB |= 3;

  while( 1) {

    // turn off all the LEDs
    all_off();

    // go to sleep
    go_to_sleep();

    // display the button count
    if( (button+1) & 1)
      led[0].r = 128;
    if( (button+1) & 2)
      led[1].r = 128;
    if( (button+1) & 4)
      led[2].r = 128;
    
    ws2812_setleds(led,3);
    _delay_ms(200);

    all_off();

    // figure out which button was pressed
    switch( button) {
    case 0:
      rainbow();
      break;
    case 1:
      flicker();
      break;
    case 2:
      flash();
      break;
    case 3:
      fade( 128, 0, 0);
      break;
    case 4:
      fade( 0, 128, 0);
      break;
    case 5:
      fade( 0, 0, 128);
      break;
    case 6:
      flash( 128, 128, 0);
      break;
    case 7:
      flash( 0, 128, 128);
      break;
    case 8:
      flash( 128, 0, 128);
      break;
    }
  }
}


#define NUM_FLICKER 25
void flicker() {
  int c;
  // random colors
  for( int i=0; i<NUM_FLICKER; i++) {
    int c1 = rand() % NUM_RGB_COLORS;
    int c2 = rand() % NUM_RGB_COLORS;
    int c3 = rand() % NUM_RGB_COLORS;

      led[0].r = pgm_read_byte(&(rgb[c1][0]));
      led[0].g = pgm_read_byte(&(rgb[c1][1]));
      led[0].b = pgm_read_byte(&(rgb[c1][2]));

      led[1].r = pgm_read_byte(&(rgb[c2][0]));
      led[1].g = pgm_read_byte(&(rgb[c2][1]));
      led[1].b = pgm_read_byte(&(rgb[c2][2]));

      led[2].r = pgm_read_byte(&(rgb[c3][0]));
      led[2].g = pgm_read_byte(&(rgb[c3][1]));
      led[2].b = pgm_read_byte(&(rgb[c3][2]));

      ws2812_setleds(led,3);
      _delay_ms(100);
  }
}


//------------------------------------------------------------
#define NUM_RAINBOW 2
void rainbow() {
  // cycle through rainbow (24 colors) 
  for( int n=0; n<NUM_RAINBOW; n++) {
    for( int i=0; i<NUM_RGB_COLORS; i++) {

      //      int i1 = ((i+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);
      //      int i2 = ((i1+(NUM_RGB_COLORS/3))%NUM_RGB_COLORS);	

      led[0].r = pgm_read_byte(&(rgb[i][0]));
      led[0].g = pgm_read_byte(&(rgb[i][1]));
      led[0].b = pgm_read_byte(&(rgb[i][2]));

      led[1].r = pgm_read_byte(&(rgb[i][0]));
      led[1].g = pgm_read_byte(&(rgb[i][1]));
      led[1].b = pgm_read_byte(&(rgb[i][2]));

      led[2].r = pgm_read_byte(&(rgb[i][0]));
      led[2].g = pgm_read_byte(&(rgb[i][1]));
      led[2].b = pgm_read_byte(&(rgb[i][2]));

      ws2812_setleds(led,3);
      _delay_ms(100);
    }
  }
}


//------------------------------------------------------------
#define NUM_FLASH 3
void flash( int r, int g, int b) {
  for( int d=1000; d>10; d /= 2) {
    for( int i=0; i<NUM_FLASH; i++) {
      memset( led, 0, sizeof(led));
      led[i].r = r;
      led[i].g = g;
      led[i].b = b;
      ws2812_setleds(led,3);
      delay_10ms( d/10);
    }
    all_off();
  }
}
    

//------------------------------------------------------------
void fade( uint8_t r, uint8_t g, uint8_t b) {
  uint8_t m = max3( r, g, b);
  for( int i=0; i<m; i++) {
    for( int n=0; n<3; n++) {
      if( r)
	led[n].r = i;
      if( g)
	led[n].g = i;
      if( b)
	led[n].b = i;
    }
    ws2812_setleds(led,3);
    _delay_ms(10);
  }
  for( int i=m; i>0; i--) {
    for( int n=0; n<3; n++) {
      if( r)
	led[n].r = i;
      if( g)
	led[n].g = i;
      if( b)
	led[n].b = i;
    }
    ws2812_setleds(led,3);
    _delay_ms(10);
  }
}
