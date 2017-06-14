#include <avr/io.h>
#include <stdint.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "freq_meas.h"


volatile uint8_t t_ovf_cnt = 0;
volatile uint8_t status = 0;
volatile uint16_t start;
volatile uint16_t stop;
volatile uint8_t stay_tovfcnt;
// TODO:
// Write the interrupt handlers

ISR(TIMER1_OVF_vect)
{
	t_ovf_cnt++;
}

ISR(TIMER1_CAPT_vect)
{
	if (status == 0) {
		start = ICR1;
		status = 1;
	} else {
		stop = ICR1;
		status = 0;
	}
	stay_tovfcnt = t_ovf_cnt;
	t_ovf_cnt = 0;
}

void freq_meas_init()
{
	/**************
	 * TC1 CONFIG *
	 **************/
	// TODO:
	// Configure the TC1 timer properly :)
	
	TCCR1B |= 1 << ICES1;
	TCCR1B |= 1 << CS11;
	TCCR1B |= 1 << CS10;
	TIMSK1 |= 1 << ICIE1;
	TIMSK1 |= 1 << TOIE1;
}

// TODO:
// Write this function. It returns the measured frequency in Hz
float get_freq()
{
	double steps;
	double period;
	steps = stay_tovfcnt * 65534 - start + stop;
	period = 64 * steps / 16000000;
	return (1 / period);
}