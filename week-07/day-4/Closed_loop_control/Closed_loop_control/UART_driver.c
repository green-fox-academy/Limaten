#include "UART_driver.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

ISR(USART_RX_vect)
{
	// Put received character into the circular buffer
	*(rx_buffer.write_ptr) = UDR0;

	// Increment the write ptr
	// Be aware that the write ptr might point to the end of the buffer.
	// In this case you have to set it back to the start of the buffer
	if (rx_buffer.write_ptr == rx_buffer.tail)
	rx_buffer.write_ptr = rx_buffer.head;
	else
	rx_buffer.write_ptr++;

}

void UART_init()
{
	// See the datasheet on page 246 for hints and table 25-9.

	// At first set the baud rate to 115200
	// The CPU clock frequency is 16MHz
	uint16_t ubbr = 8;
	UBRR0H = ubbr >> 8;
	UBRR0L = ubbr;

	// Set the following frame format: 8N1
	// It's set by default to 8N1

	// Enable TX
	UCSR0B |= 1 << TXEN0;

	// Enable RX
	UCSR0B |= 1 << RXEN0;

	// Enable RX interrupt
	UCSR0B |= 1 << RXCIE0;

	// Initialize circular buffer pointers, they should point to the head of the buffer
	rx_buffer.head = &(rx_buffer.buffer[0]);
	rx_buffer.tail = &(rx_buffer.buffer[RX_CIRC_BUFF_LEN - 1]);
	rx_buffer.read_ptr = rx_buffer.head;
	rx_buffer.write_ptr = rx_buffer.head;
}

void UART_send_character(char character)
{
	// This function can send a character through UART with polling method
	// See page 247 of the datasheet for hints, be aware that the code in the datasheet has a problem :)

	// Wait for empty USART buffer register
	while ( !( UCSR0A & (1 << UDRE0)) );

	// Put data to USART buffer register
	UDR0 = character;
}

char UART_get_character()
{
	// Wait for data in the circular buffer, this can be detected if the write and read pointers are pointing to the same memory block
	while ((rx_buffer.read_ptr) == (rx_buffer.write_ptr));

	// Save the data to a temporary variable
	char to_return = *(rx_buffer.read_ptr);

	// Increment the read ptr
	// Be aware that the read ptr might point to the end of the buffer.
	// In this case you have to set it back to the start of the buffer
	if (rx_buffer.read_ptr == rx_buffer.tail)
	rx_buffer.read_ptr = rx_buffer.head;
	else
	rx_buffer.read_ptr++;


	// Return the read character
	return to_return;
}

uint8_t UART_is_buffer_empty()
{
	if (rx_buffer.read_ptr == rx_buffer.write_ptr)
	return 1;
	else
	return 0;
}