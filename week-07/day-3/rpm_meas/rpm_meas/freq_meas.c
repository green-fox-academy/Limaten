#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <math.h>
#include "freq_meas.h"

static volatile uint16_t last_reg_value;
static volatile uint16_t prev_reg_value;
static volatile uint16_t ovf_value;
static volatile uint16_t ovf_cntr;

ISR(TIMER1_CAPT_vect)
{
	ovf_value = ovf_cntr;
	ovf_cntr = 0;
	prev_reg_value = last_reg_value;
	last_reg_value = ICR1;
}

ISR(TIMER1_OVF_vect)
{
	ovf_cntr++;
}

void freq_meas_init()
{
	// Variable initialization
	prev_reg_value = last_reg_value = ovf_cntr = 0;

	/**************
	 * TC1 CONFIG *
	 **************/
	// TODO:
	// Configure the TC1 timer properly :)

	// TC1 Input capture interrupt enable
	TIMSK1 |= 1 << ICIE1;
	// TC1 overflow interrupt enable
	TIMSK1 |= 1 << TOIE1;
	// TC1 clock select, this will also start the timer!
	TCCR1B = CS_DEFAULT;
}

float get_freq()
{
	// The interrupts must be disabled while accessing variables which are used in interrupt handlers
	cli();
	// Copy the used variables as fast as possible.
	uint16_t last = last_reg_value;
	uint16_t prev = prev_reg_value;
	uint16_t ovf = ovf_value;
	sei();

	// This difference can be negative, that is why int32_t is used!
	// One of the variables should be casted to int32_t to avoid unexpected underflow
	int32_t diff = (int32_t)last - (int32_t)prev;

	// Steps will be always positive, so uint32_t can be used.
	// One of the variables should be casted to uint32_t to avoid unexpected overflof during multiplication
	uint32_t steps = ((uint32_t)ovf) * (OVF_STEPS) + diff;


	// One of the variables should be casted to float
	float period = TC1_STEP_TIME_S * (float)steps;
	float freq =  1 / period;

	// If you divide with zero in C the result will be NaN (not a number)
	// Check if the frequency is Nan, and return negative number in this case
	if (isnan(freq) || isinf(freq))
		return -1;
	else
		return freq;
}