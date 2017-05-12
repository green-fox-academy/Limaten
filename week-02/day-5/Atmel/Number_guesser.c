#include <avr/io.h>			// This header contains the definitions for the io registers
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <avr/interrupt.h>

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

int hol;
int button = 1;

void UART_Init()
{
	// At first set the baud rate to 9600
	// The CPU clock frequency is 16MHz
	UBRR0H = 103 >> 8;
	UBRR0L = 103;
	
	// Enable TX
	UCSR0B |= 1 << TXEN0;
	
	// Enable RX
	UCSR0B |= 1 << RXEN0;
	
	// Set PORTB5 as output	
	DDRB |= 1 << DDRB5;
	
	// Set the PCINT7 bit of PCMSK0 register.
	PCMSK0 |= 1 << PCINT7;
	
	// Enable pin interrupt on change 0 interrupts.
	PCICR |= 1 << PCIE0;
	
	// Finally, enable the interrupts globally
	sei();
}

void UART_SendCharacter(char character)
{

	// Wait for empty buffer
	while(!(UCSR0A & (1 << UDRE0)));
	
	// Put data to buffer
	UDR0 = character;
}

char UART_GetCharacter()
{

	// Wait for data received
	while(!(UCSR0A & (1 << RXC0)));

	// Get data to buffer
	return UDR0;
}

high(){
	for(int i = 0; i < hol; i++){
		_delay_ms(125);
		PORTB |= 1 << PORTB5;
		_delay_ms(125);
		PORTB &= ~(1 << PORTB5);
	}
}

low(){
	for(int i = 0; i < hol; i++){
		_delay_ms(125);
		PORTB |= 1 << PORTB5;
		_delay_ms(125);
		PORTB &= ~(1 << PORTB5);
	}
}

win(){
	for(int i = 0; i < 100; i++){
		PINB |= 1 << PINB5;
		_delay_ms(25);
	}
}

ISR(PCINT0_vect){
	button++;
	if(button % 2 == 0){
		if(hol == 2){
			high();
		}else{
			low();
		}
	}
}

int guesser()
{
	srand(time(NULL));
	int lives = 5;
	int randomNumber = 1;
	int maxNumber;
	int playersNumber;
	printf("\n\n\rNew game!\r\nPlease enter the range, from 1 to X:\r\n");
	scanf("%d", &maxNumber);
	randomNumber += rand() % maxNumber;
	printf("I've the number between 1 and %d. You have %d lives.\r\n", maxNumber, lives);

	while(1){
		if(lives == 1){
			printf("Last chance!\r\n");
		}
		scanf("%d", &playersNumber);
		printf("%d\r\n", playersNumber);
		if(playersNumber == randomNumber){
			printf("That's my number. Congratulations!\r\n");
			win();
			return 0;
			}else if(playersNumber > randomNumber){
				lives--;
				printf("Too high. You have %d lives\r\n", lives);
				hol = 2;
				high();
			}else{
				lives--;
				printf("Too low. You have %d lives\r\n", lives);
				hol = 1;
				low();
			}
		if(lives == 0){
			printf("\nYou lost.\r\nGAME OVER\r\n");
			printf("My number was %d.\r\n", randomNumber);
			return 0;
		}
	}
}

int main(void)
{
	UART_Init();


	// magic
	FILE UART_output = FDEV_SETUP_STREAM(UART_SendCharacter, NULL, _FDEV_SETUP_WRITE);
	stdout = &UART_output;
	FILE UART_input = FDEV_SETUP_STREAM(NULL, UART_GetCharacter, _FDEV_SETUP_READ);
	stdin = &UART_input;

	// Loop that runs forever
	while(1){
		guesser();
	}
}