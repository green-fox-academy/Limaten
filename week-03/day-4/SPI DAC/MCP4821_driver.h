// Multiple inclusion guard
#ifndef _MCP4821_DRIVER_H
#define _MCP4821_DRIVER_H

#include <stdint.h>

#define SPI_MOSI_PORT		PORTB
#define SPI_MOSI_PORT_POS	PORTB3
#define SPI_MOSI_DDR		DDRB
#define SPI_MOSI_DDR_POS	DDRB3

#define SPI_SCK_PORT		PORTB
#define SPI_SCK_PORT_POS	PORTB5
#define SPI_SCK_DDR			DDRB
#define SPI_SCK_DDR_POS		DDRB5

#define SPI_SS_PORT			PORTB
#define SPI_SS_PORT_POS		PORTB2
#define SPI_SS_DDR			DDRB
#define SPI_SS_DDR_POS		DDRB2

#define SPI_CPOL		1		// Clock polarity
#define SPI_CPHA		1		// Clock edge
#define SPI_SPR			0b11	// Speed of SPI clock

#define SPI_DATA_MAX	4095

// The "data" member will be stored at first in the memory
// The "shutdown" bit will come after that, and so on
typedef struct {
	uint16_t data:12;
	uint16_t shutdown:1;
	uint16_t gain:1;
	uint16_t dont_care:1;
	uint16_t start_zero:1;
} MCP4821_Data_t;

void MCP4821_Init();
void MCP4821_SendRawData(uint16_t data);
void MCP4821_SendData(MCP4821_Data_t* data);

#endif // _MCP4821_DRIVER_H