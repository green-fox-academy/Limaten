#include "MCP4821_driver.h"
#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/delay.h>

void SystemInit() {
	// Call the DAC driver init function
	MCP4821_Init();
}

int main(void) {
	// Don't forget to call the init function :)
	SystemInit();

	// DAC test data
	// gain = 2, data is 0xFFF so the output voltage should be 4.048V
	MCP4821_Data_t DAC_data;
	DAC_data.start_zero = 0;
	DAC_data.dont_care = 0;
	DAC_data.gain = 0;
	DAC_data.shutdown = 1;
	DAC_data.data = 0xFFF;

	// Send the data structure
	MCP4821_SendData(&DAC_data);

	// Infinite loop
	while (1) {
		_delay_ms(250);
	}
}