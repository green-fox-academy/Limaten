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
		for(int i = 0; i < 100; i++) {
			OCR0A = i * 255 / 100;
			_delay_ms(10);
		}
		for(int i = 0; i < 100; i++) {
			OCR0A = (100 -i) * 255 / 100;
			_delay_ms(10);
		}
    }
}

