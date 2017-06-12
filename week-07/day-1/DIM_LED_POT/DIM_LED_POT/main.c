#include <avr/io.h>
#include "DIM_LED_POT.h"
#include "ADC_DRIVER.h"
#include "UART_driver.h"

#define F_CPU	16000000
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

int main(void)
{
	
	system_init();
	
	ADC_init();
	
	UART_Init();
	
	sei();
	//duty_time(100);
	
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;
	
	int percent;
	
	while (1)
	{
		percent = (100 * (ADC_read() >> 2)) / 255;
		printf("%d\n", percent);
		duty_time(percent);
	}
}

