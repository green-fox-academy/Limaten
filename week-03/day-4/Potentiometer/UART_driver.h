#ifndef _UART_DRIVER_H_
#define _UART_DRIVER_H_

#define RX_CIRC_BUFF_LEN 25

volatile struct CircularBuffer {
	char buffer[RX_CIRC_BUFF_LEN];
	char* head;
	char* tail;
	char* write_ptr;
	char* read_ptr;
} rx_buffer;

void UART_Init();
void UART_SendCharacter(char character);
char UART_GetCharacter();

#endif /* _UART_DRIVER_H_ */