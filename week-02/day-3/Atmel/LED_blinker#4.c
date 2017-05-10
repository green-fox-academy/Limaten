#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

// Create a variable which will be a counter variable, initialize it with 0. This time it has to be global.
uint8_t cntr = 0;
// This will be the maximal value of our counter. This time it has to be global.
const uint8_t cntr_max = 10;

// Write here the interrupt handler function. The vector name starts with TIMER0 ;). Use Ctrl+Space to find the proper vector name!
// Do the same thing in the interrupt handler as before
// If the counter not reached the maximum then increment it.
// Else toggle the LED and set the counter to zero.
// This time you don't have to do anything with the flags, the MCU does it automatically.
ISR(TIMER0_OVF_vect){
	if(cntr < cntr_max){
		cntr++;
		}else{
		PINB |= 1 << PINB5;
		cntr = 0;
	}
}

void init()
{
	// Set the prescaler to 1024 division. See at the TC0 control register in the datasheet!
	// With this you also set the clock source to CLK_io and you will also turn on the timer!
	TCCR0B |= 0x05;
	// Set the PB5 LED pin to output
	DDRB |= 1 << DDRB5;
	// Enable the TC0 overflow interrupt
	TIMSK0 |= 1 << TOIE0;
	// Enable the interrupts globally
	sei();
}

int main(void)
{
	// Don't forget to call the init function!
	init();
	while (1)
	{
		//Nothing to do here, everithing is done in interrupt :)
	}
}