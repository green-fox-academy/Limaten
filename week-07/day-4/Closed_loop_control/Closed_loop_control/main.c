#include "freq_meas.h"
#include "UART_driver.h"
#include "AC_driver.h"
#include "ADC_DRIVER.h"
#include "PWM.h"
#include "TC74_driver.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

#define LED_DDR			DDRB
#define LED_DDR_POS		DDRB5
#define LED_PIN			PINB
#define LED_PIN_POS		PINB5
#define LED_PORT		PORTB
#define LED_PORT_POS	PORTB5

#define MAX_RMP	55
#define MAX_ADC 10.23

void system_init()
{
	LED_DDR |= 1 << LED_DDR_POS;
	AC_driver_init();
	freq_meas_init();
	UART_init();
	pwm_init();
	ADC_init();
	TWI_init();
	sei();
}

int main(void)
{

	// Don't forget to call the init function :)
	system_init();
	float p = 5;
	float i = 0.1;
	int ref;
	int ctrl_out_max = 99;
	int ctrl_out_min = 0;
	float err;
	float integral = 0;
	int ctrl_out;
	int temp;
	// Setting up STDIO input and output buffer
	// You don't have to understand this!
	//----- START OF STDIO IO BUFFER SETUP
	FILE UART_output = FDEV_SETUP_STREAM((void *)UART_send_character, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, (void *)UART_get_character, _FDEV_SETUP_READ);
	stdin = &UART_input;
	//----- END OF STDIO IO BUFFER SETUP

	// Try printf
	printf("Startup...\r\n");
	int adc_percent;
	//int uart_percent;
	// Infinite loop
	while (1) {
		//LED_PORT |= 1 << LED_PORT_POS;
		/*_delay_ms(500);
		LED_PORT &= ~(1 << LED_PORT_POS);
		_delay_ms(500);*/
		//printf("%f Hz\n", get_freq());
		//printf("%f RPM\n", get_rpm());
		//adc_percent = ADC_read() / 10.23;
		//printf("adc_percent: %d\n", adc_percent);
		//duty_time(adc_percent);
		_delay_ms(10);
		ref = 10 + (ADC_read() / 10.23) * 0.3;
		temp = get_temperature(TC74A0_ADRESS);
		err = temp - ref;
		integral = integral + err;
		ctrl_out = p * err + i * integral;
		//printf("ctrl_out before: %d\n", ctrl_out);
		if (ctrl_out < ctrl_out_min) {
			ctrl_out = ctrl_out_min;
			integral = integral - err;
		}
		else if (ctrl_out > ctrl_out_max) {
			ctrl_out = ctrl_out_max;
			integral = integral - err;
		}
		//printf("ctrl_out after: %d\n", ctrl_out);
		duty_time(ctrl_out);
		printf("duty_time: %d%%\t%.2f RPM\tref: %dC\ttmperature: %dC\n", ctrl_out, get_rpm(), ref, temp);
	}
}