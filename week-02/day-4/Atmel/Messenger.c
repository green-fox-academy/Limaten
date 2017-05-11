#include <avr/io.h>			// This header contains the definitions for the io registers
#include <stdint.h>

#define F_CPU	16000000	// This definition tells to _delay_ms() that the CPU runs at 16MHz
#include <util/delay.h>		// This header contains the _delay_ms() function

void UART_Init()
{
	// Write this function
	// See the datasheet on page 246 for hints and table 25-9.
	//---------------------------------
	//TODO:
	// At first set the baud rate to 9600
	// The CPU clock frequency is 16MHz
	UBRR0H = 103 >> 8;
	UBRR0L = 103;
	
	//TODO:
	// Set the following frame format: 8N1
	
	//TODO:
	// Enable TX
	UCSR0B |= 1 << TXEN0;
	//TODO:
	// Enable RX
	UCSR0B |= 1 << RXEN0;
}

void UART_SendCharacter(char character)
{
	// Write this function, which can send a character through UART will polling method
	// See page 247 of the datasheet for hints, be aware that the code in the datasheet has a problem :)
	//---------------------------------
	//TODO:
	// Wait for empty buffer
	while(!(UCSR0A & (1 << UDRE0)));
	//TODO:
	// Put data to buffer
	UDR0 = character;
}

char UART_GetCharacter()
{
	// Write this function, which waits for a character and returns when one is received
	// See page 249 of the datasheet for hints, be aware that the code in the datasheet has a problem :)
	//---------------------------------
	//TODO:
	// Wait for data received
	while(!(UCSR0A & (1 << RXC0)));
	//TODO:
	// Get data from buffer
	return UDR0;
}

int main(void)
{
	char character;
	//Don't forget to call the init function :)
	UART_Init();

	// Loop that runs forever
	while (1) {
		// Receive a character
		character = UART_GetCharacter();
		// Send the character back
		UART_SendCharacter(character);
	}
}