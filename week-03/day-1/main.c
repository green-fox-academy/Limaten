#include <avr/io.h>
#include <time.h>
#include <avr/interrupt.h>

int cntr = 0;
int cntr_max = 32;

void init(){
	DDRD = 0xFF;
	TCCR0B |= 0x05;
	TIMSK0 |= 1 << TOIE0;
	sei();
}

ISR(TIMER0_OVF_vect){
	int i = 0;
	while(i < 8){
		if(cntr < cntr_max){
			cntr++;
		}else{
			PORTD = 1 << i;
			cntr = 0;
			i++;
		}
	}
}

int main(void)
{
	init();
	
    while (1) 
    {
		
	}
}
