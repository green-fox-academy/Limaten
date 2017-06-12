#include <avr/io.h>
#include "PWM.h"

void PWM_init()
{
	DDRD |= 1 << DDRD6;
	
	PORTD |= 1 << PORTD6;
	
	TCCR0A |= 1 << WGM00;
	TCCR0A |= 1 << WGM01;
	
	TCCR0B |= 1 << CS00;
	
	TCCR0A |= 1 << COM0A1;
}

void duty_time(int percent)
{
	uint8_t dt =  percent * 2.55;
	printf("dt: %d\n", dt);
	OCR0A = dt;
}