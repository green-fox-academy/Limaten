/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
	{1,0,0,1,0,0,1},
	{0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0},
	{1,0,0,1,0,0,1},
	{0,0,1,0,0,1,0},
};

// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);
// Mutex global variable
osMutexId led_matrix_mutex_id;

struct column_row {
	GPIO_TypeDef *gpio_port;
	uint32_t pin_num;
};

struct column_row row[5] = {
		{GPIOC, GPIO_PIN_7},
		{GPIOC, GPIO_PIN_6},
		{GPIOG, GPIO_PIN_6},
		{GPIOB, GPIO_PIN_4},
		{GPIOG, GPIO_PIN_7}
};

struct column_row column[7] = {
		{GPIOI, GPIO_PIN_0},
		{GPIOH, GPIO_PIN_6},
		{GPIOI, GPIO_PIN_3},
		{GPIOI, GPIO_PIN_2},
		{GPIOA, GPIO_PIN_15},
		{GPIOA, GPIO_PIN_8},
		{GPIOB, GPIO_PIN_15},
};

/* Private function prototypes -----------------------------------------------*/
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);
/* Private functions ---------------------------------------------------------*/


// TODO:
// Write this function!
void led_matrix_set(uint8_t in_row, uint8_t in_col, uint8_t state) {
	// TODO:
	// Wait for the mutex
	//osMutexWait(led_matrix_mutex_id, osWaitForever);
	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	HAL_GPIO_WritePin(row[in_row].gpio_port, row[in_row].pin_num, state);
	HAL_GPIO_WritePin(column[in_col].gpio_port, column[in_col].pin_num, state);
	// TODO:
	// Release the mutex
	//osMutexRelease(led_matrix_mutex_id);
}

// TODO:
// Write this function!
void led_matrix_update_thread(void const *argument)
{
	// TODO:
	// Initialize the pins as outputs and the led_matrix_state 2D array
	led_matrix_gpio_init();

	// TODO:
	// Create a mutex
	// Use the LED_MATRIX_MUTEX_DEF
	led_matrix_mutex_id = osMutexCreate(osMutex(LED_MATRIX_MUTEX_DEF));

	LCD_UsrLog("led_matrix - initialized\n");

	// Infinite loop
	while (1) {
		// TODO:
		// Implement the led matrix updater functionality

		// Step 1:
		// Iterate through every column or row

			// Step 2:
			// Wait for the mutex
		osMutexWait(led_matrix_mutex_id, osWaitForever);

			// Step 3:
			// Turn on the column or row


			// Step 4:
			// Turn on the leds in that column or row
		for(int i = 0; i < LED_MATRIX_ROWS; i++) {
			for (int j = 0; j < LED_MATRIX_COLS; j++) {
				led_matrix_set(i, j, led_matrix_state[i][j]);
				osDelay(100);
				led_matrix_set(i, j, 0);
			}
		}

			// Step 5:
			// Release the mutex
		osMutexRelease(led_matrix_mutex_id);

			// Step 6:
			// Delay
		osDelay(250);

			// Step 7:
			// Turn off the column or row
	}

	// Terminating thread
	while (1) {
		LCD_ErrLog("led_matrix - terminating...\n");
		osThreadTerminate(NULL);
	}
}

// This thread is a waterfall type animation
void led_matrix_waterfall_thread(void const *argument)
{
	while (1) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
				led_matrix_set(r, c, 1);
				osDelay(50);
				led_matrix_set(r, c, 0);
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}


void led_matrix_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_InitDef.Pin = GPIO_PIN_8 | GPIO_PIN_15;
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_4 | GPIO_PIN_15;
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init(GPIOB, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_Init(GPIOC, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	__HAL_RCC_GPIOG_CLK_ENABLE();
	HAL_GPIO_Init(GPIOG, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_6;
	__HAL_RCC_GPIOH_CLK_ENABLE();
	HAL_GPIO_Init(GPIOH, &GPIO_InitDef);

	GPIO_InitDef.Pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
	__HAL_RCC_GPIOI_CLK_ENABLE();
	HAL_GPIO_Init(GPIOI, &GPIO_InitDef);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
