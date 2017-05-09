#include <avr/io.h>			// This header contains the definitions for the io registers

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

int main(void)
{
	// The LED is on PORTB at pin 5
	// See http://www.atmel.com/Images/Atmel-42381-ATmega168PB-Xplained-Mini_UserGuide.pdf at page 13 for more info

	// We would like to turn on the LED, so PORTB pin 5 has to be set to output first.
	// This can be made by writing the bit "1" to the DDRB register 6th bit.
	// Little bit tricky, because the pin numbering starts from 0. So the first pin of PORTB is PORTB0.
	// Hence PORTB5 is the 6th bit of PORTB.

	// Let's turn on DDRB5 to 1! The easiest way is to use a binary literal.
	// DDRB = 0b00100000;
	// But this is too easy for us :). Usually we want to keep the other bits, so we use the following expression instead:
	DDRB = DDRB | 0b00100000;

	// Or simply
	// DDRB |= 0b00100000;

	// Or using the definitions in io.h
	// DDRB |= 1 << DDRB5;
	// This one is the best, because the io.h contains the DDRB5 definition, we don't need to bother with the numbering of pins.

	// Loop that runs forever
	while (1) {
		// Now turn on the LED by writing the bit "1" to PORTB 6th bit (PORTB5)
		PORTB |= 1 << PORTB5;
		_delay_ms(500);	// Here the CPU will wait for 500ms

		// Now turn off the LED by writing the bit "0" to PORTB 6th bit (PORTB5)
		// The PORTB |= 0 << PORTB5 will not work. Do you know why?
		PORTB &= ~(1 << PORTB5);
		_delay_ms(500);	// Here the CPU will wait for 500ms
	}
}