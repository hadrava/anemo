#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/cpufunc.h>

int main(void) {
	_delay_ms(4000);
	DDRB |= _BV(PB0) | _BV(PB1);

	while (1) {
		PORTB = (PINB >> 3) & (_BV(PB0) | _BV(PB1));
	}
}
