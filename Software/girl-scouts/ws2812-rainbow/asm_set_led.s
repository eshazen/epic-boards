;;; asm_set_led( v)
;;;
;;; for now, just set port B to passed value

#define __SFR_OFFSET 0		; use 0 for the I/o reg offset
#include <avr/io.h>

PORTB = 0x18	

.global asm_set_led

.section .text

asm_set_led:
	out	PORTB, r24
	ret
