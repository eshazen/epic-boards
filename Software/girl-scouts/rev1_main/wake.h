//
// support for wake-on-interrupt for ATTiny85
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void go_to_sleep();

volatile uint8_t button;
