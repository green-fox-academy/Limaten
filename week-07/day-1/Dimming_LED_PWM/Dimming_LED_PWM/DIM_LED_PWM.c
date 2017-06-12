#include <avr/io.h>
#include "DIM_LED_PWM.h"

void system_init()
{
	DDRD |= 1 << DDRD6;
	
	PORTD |= 1 << PORTD6;
	
	TCCR0A |= 1 << WGM00;
	TCCR0A |= 1 << WGM01;
	TCCR0B |= 1 << WGM02;
	
	TCCR0B |= 1 << CS00;
	
	TCCR0A |= 1 << COM0A0;
}

void duty_time()
{
//	uint8_t dt = 100 * 255 / DUTY; 
	OCR0A = 80;
}