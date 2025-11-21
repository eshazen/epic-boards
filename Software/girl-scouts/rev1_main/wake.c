//
// support for wake-on-interrupt for ATTiny85
//
// From:
// https://bigdanzblog.wordpress.com/2014/08/10/attiny85-wake-from-sleep-on-pin-state-change-code-example/
//

#include "wake.h"

void go_to_sleep() {
  PORTB |= _BV(0);		/* pull-up on PB0 */

  GIMSK |= _BV(PCIE);		/* enable pin change interrupt */
  PCMSK |= _BV(PCINT1) | _BV(PCINT0); /* Use PB0, PB1 as interrupts */
  ADCSRA &= ~_BV(ADEN);		/* ADC off */

  set_sleep_mode( SLEEP_MODE_PWR_DOWN); // set sleep mode to power-down
  sleep_enable(); // set sleep enable
  sei(); // enable interrupts
  sleep_cpu();
}

