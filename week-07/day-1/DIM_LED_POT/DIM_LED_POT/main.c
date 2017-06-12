#include <avr/io.h>
#include "DIM_LED_PWM.h"
#define F_CPU	16000000
#include <util/delay.h>

int main(void)
{
	
	system_init();
	
	duty_time();
	
	while (1)
	{
	}
}

