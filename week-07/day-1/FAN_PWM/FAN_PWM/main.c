#include <avr/io.h>
#include "PWM.h"
#include "ADC_DRIVER.h"
#include "UART_driver.h"

#define F_CPU	16000000
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

int main(void)
{
	
	PWM_init();
	
	ADC_init();
	
	UART_init();
	
	sei();
	
	FILE UART_output = FDEV_SETUP_STREAM(UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	
	int adc_percent;
	int uart_percent;
	char buffer[5];
	
	while (1)
	{
		(scanf("%s", &buffer));
		uart_percent = atoi(buffer);
		printf("uart_percent: %d\n", uart_percent);
		duty_time(uart_percent);
		/*
		adc_percent = ADC_read() / 10.23;
		printf("adc_percent: %d\n", adc_percent);
		duty_time(adc_percent * uart_percent);
		*/
	}
}

