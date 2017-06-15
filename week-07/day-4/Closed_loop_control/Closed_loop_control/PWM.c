#include <avr/io.h>
#include "PWM.h"

void pwm_init()
{
	DDRB |= 1 << DDRB3;
	
	PORTB |= 1 << PORTB3;
	
	TCCR2A |= 1 << WGM20;
	TCCR2A |= 1 << WGM21;
	
	TCCR2B |= 1 << CS20;
	
	TCCR2A |= 1 << COM2A1;
}

void duty_time(int percent)
{
	uint8_t dt =  percent * 2.55;
	//printf("dt: %d\n", dt);
	OCR2A = dt;
}