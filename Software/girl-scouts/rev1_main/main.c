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

#define NUM_LED 3

struct cRGB led[NUM_LED];
struct cRGB temp;

#define BRITE 100

//
// display options
//
#define NUM_OPTIONS 4
void rainbow();
void flicker();
void flash();
void spin();

// needed but not used
ISR(PCINT0_vect) {
  if( !(PINB & _BV(0)))
    button = (button + 1) % NUM_OPTIONS;
  if( !(PINB & _BV(1)))
    button = (button - 1) % NUM_OPTIONS;
}


void all_off() {
  memset( led, 0, sizeof(led));
    ws2812_setleds(led,NUM_LED);
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
    
    ws2812_setleds(led,NUM_LED);
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
      spin();
      break;
//    case 4:
//      fade( 0, 128, 0);
//      break;
//    case 5:
//      fade( 0, 0, 128);
//      break;
    }
  }
}


// set LED n (0-2) to color from table in flash
void set_led_table( int n, int c1) {
  led[n].r = pgm_read_byte(&(rgb[c1][0]));
  led[n].g = pgm_read_byte(&(rgb[c1][1]));
  led[n].b = pgm_read_byte(&(rgb[c1][2]));
}


#define NUM_FLICKER 25
void flicker() {
  int c;
  // random colors
  for( int i=0; i<NUM_FLICKER; i++) {
    int c1 = rand() % NUM_RGB_COLORS;
    int c2 = rand() % NUM_RGB_COLORS;
    int c3 = rand() % NUM_RGB_COLORS;

    set_led_table( 0, c1);
    set_led_table( 1, c2);
    set_led_table( 2, c3);

    ws2812_setleds(led,NUM_LED);
    _delay_ms(100);
  }
}


//------------------------------------------------------------
#define NUM_RAINBOW 2
void rainbow() {
  // cycle through rainbow (24 colors) 
  for( int n=0; n<NUM_RAINBOW; n++) {
    for( int i=0; i<NUM_RGB_COLORS; i++) {

      set_led_table( 0, i);
      set_led_table( 1, i);
      set_led_table( 2, i);

      ws2812_setleds(led,NUM_LED);
      _delay_ms(100);
    }
  }
}


//------------------------------------------------------------
#define FLASH_CYCLES 3
#define FLASH_MAX_DELAY 300
void flash() {
  int c = 0;
  for( int k=0; k<FLASH_CYCLES; k++) {
    for( int d=FLASH_MAX_DELAY; d>10; d /= 2) {
      for( int i=0; i<NUM_LED; i++) {
	memset( led, 0, sizeof(led));
	set_led_table( i, c);
	ws2812_setleds(led,NUM_LED);
	delay_10ms( d/10);
	c = (c+1) % NUM_RGB_COLORS;
      }
      all_off();
    }
    for( int d=2; d<=FLASH_MAX_DELAY; d *= 2) {
      for( int i=0; i<NUM_LED; i++) {
	memset( led, 0, sizeof(led));
	set_led_table( i, c);
	ws2812_setleds(led,NUM_LED);
	delay_10ms( d/10);
	c = (c+1) % NUM_RGB_COLORS;
      }
      all_off();
    }
  }
}
    
#define NUM_SPIN 15
#define SPIN_DELAY 250
void spin() {
  int colr[NUM_LED];
  for( int i=0; i<NUM_LED; i++)
    colr[i] = NUM_RGB_COLORS * i / NUM_LED;
  for( int i=0; i<NUM_SPIN; i++) {
    for( int n=0; n<NUM_LED; n++)
      set_led_table( n, colr[n]);
    ws2812_setleds(led,NUM_LED);
    delay_10ms( SPIN_DELAY/10);
    int t = colr[0];
    for( int i=0; i<NUM_LED-1; i++)
      colr[i] = colr[i+1];
    colr[NUM_LED-1] = t;
  }
}
