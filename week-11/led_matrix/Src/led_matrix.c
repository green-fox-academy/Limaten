/* Includes ------------------------------------------------------------------*/
#include "led_matrix.h"
#include "stm32f7xx_hal.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "stm32f7xx_hal_adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef adc_handle;
ADC_ChannelConfTypeDef adc_ch;
osMessageQDef(msg, 1, uint32_t);              // Define message queue
osMessageQId  msg_id;

// Each LED state is stored in this 2D array
GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
	{0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0},
	{1,0,0,1,0,0,1},
	{0,0,1,0,0,1,0},
	{0,1,0,0,1,0,0},
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
	osMutexWait(led_matrix_mutex_id, osWaitForever);
	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state [in_row][in_col] = state;
	// TODO:
	// Release the mutex
	osMutexRelease(led_matrix_mutex_id);
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
		for(int i = 0; i < LED_MATRIX_ROWS; i++) {
			for (int j = 0; j < LED_MATRIX_COLS; j++) {

			// Wait for the mutex
			osMutexWait(led_matrix_mutex_id, osWaitForever);

			// Turn on the leds in that column or row
			HAL_GPIO_WritePin(column[j].gpio_port, column[j].pin_num, !led_matrix_state[i][j]);

			// Release the mutex
			osMutexRelease(led_matrix_mutex_id);

			}
			//row up
			HAL_GPIO_WritePin(row[i].gpio_port, row[i].pin_num, 1);
			osDelay(1);
			//row down
			HAL_GPIO_WritePin(row[i].gpio_port, row[i].pin_num, 0);
		}
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
	led_matrix_gpio_init();
	uint32_t value;
	osEvent  evt;
	while (1) {
		for (uint8_t r = 0; r < LED_MATRIX_ROWS; r++) {
			for (uint8_t c = 0; c < LED_MATRIX_COLS; c++) {
				led_matrix_set(r, c, 1);
				evt = osMessageGet(msg_id, osWaitForever);
				value = evt.value.v;
				osDelay(25);
				led_matrix_set(r, c, 0);
			}
		}
	}

	while (1) {
		LCD_ErrLog("led_matrix_waterfall - terminating...\n");
		osThreadTerminate(NULL);
	}
}


void led_matrix_adc_thread(void const *argument)
{
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(0);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	adc_handle.State = HAL_ADC_STATE_RESET;
	adc_handle.Instance = ADC3;
	adc_handle.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	adc_handle.Init.Resolution = ADC_RESOLUTION_12B;
	adc_handle.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	adc_handle.Init.DMAContinuousRequests = DISABLE;
	adc_handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	adc_handle.Init.ContinuousConvMode = ENABLE;
	adc_handle.Init.DiscontinuousConvMode = DISABLE;
	adc_handle.Init.ScanConvMode = DISABLE;

	adc_ch.Channel      = ADC_CHANNEL_0;
	adc_ch.SamplingTime = ADC_SAMPLETIME_480CYCLES;

	// ADC inits
	HAL_ADC_Init(&adc_handle);
	HAL_ADC_ConfigChannel(&adc_handle, &adc_ch);
	uint32_t adc_value;

	//msg_id = osMessageCreate(osMessageQ(msg), NULL);
	HAL_ADC_Start(&adc_handle);
	while (1) {

		//HAL_ADC_PollForConversion(&adc_handle, HAL_MAX_DELAY);
		adc_value = HAL_ADC_GetValue(&adc_handle);
		//osMessagePut(msg_id, adc_value, osWaitForever);
		char buff[100];
		sprintf(buff, "%d", adc_value);
		BSP_LCD_ClearStringLine(0);
		BSP_LCD_DisplayStringAtLine(0, (uint8_t *)buff);
		osDelay(10);
	}

	while (1) {
		LCD_ErrLog("ADC - terminating...\n");
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
