#include <avr/io.h>
#include "DIM_LED_PWM.h"

void system_init()
{
	DDRD |= 1 << DDRD6;
	
	PORTD |= 1 << PORTD6;
	
	TCCR0A |= 1 << WGM00;
	TCCR0A |= 1 << WGM01;
	
	TCCR0B |= 1 << CS00;
	
	TCCR0A |= 1 << COM0A1;
}

void duty_time(uint8_t percent)
{
	uint8_t dt =  percent * 255 / 100;
	OCR0A = dt;
}