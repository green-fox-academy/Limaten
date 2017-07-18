/* Includes ------------------------------------------------------------------*/
#include "socket_client.h"
//#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_COLS 7
#define FIRST_SQUARE 108
#define SQUARE_SIDE 54
/* Private typedef -----------------------------------------------------------*/
struct field {
	uint8_t status; // 0 = water | 1 = ship | 2 = X (hit ship)
	uint16_t x;
	uint16_t y;
};

GPIO_PinState led_matrix_state[LED_MATRIX_ROWS][LED_MATRIX_COLS] = {
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
};

struct column_row {
	GPIO_TypeDef *gpio_port;
	uint32_t pin_num;
};

struct column_row row[LED_MATRIX_ROWS] = {
		{GPIOC, GPIO_PIN_7},
		{GPIOC, GPIO_PIN_6},
		{GPIOG, GPIO_PIN_6},
		{GPIOB, GPIO_PIN_4},
		{GPIOG, GPIO_PIN_7}
};

struct column_row column[LED_MATRIX_COLS] = {
		{GPIOI, GPIO_PIN_0},
		{GPIOH, GPIO_PIN_6},
		{GPIOI, GPIO_PIN_3},
		{GPIOI, GPIO_PIN_2},
		{GPIOA, GPIO_PIN_15},
		{GPIOA, GPIO_PIN_8},
		{GPIOB, GPIO_PIN_15},
};
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SERVER_PORT 		24862
#define SERVER_IP 			"10.27.6.85"
#define DATA_BUFFER_SIZE 	2
#define ROW 				6
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef ts_state;
TS_StateTypeDef *ts_state_ptr = &ts_state;
struct field array[LED_MATRIX_COLS][LED_MATRIX_ROWS];
struct field small_array[LED_MATRIX_COLS][LED_MATRIX_ROWS];
	// Mutex definition
osMutexDef(LED_MATRIX_MUTEX_DEF);
	// Mutex global variable
osMutexId led_matrix_mutex_id;
	//Message queue definition
osMessageQDef(led_message_q, 3, uint32_t);
	//Message queue ID
osMessageQId led_message_q_id;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void clear_table();
void draw_small_table();
void fill_field();
void led_matrix_gpio_init();
void led_matrix_set(uint8_t row, uint8_t col, uint8_t state);

// TODO:
// Implement this function!
void socket_client_thread(void const *argument)
{
	while (is_ip_ok() == 0) {
		osDelay(500);
	}

	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(SERVER_PORT);
	addr_in.sin_addr.s_addr = inet_addr(SERVER_IP);

	uint8_t connected = -1;
	uint8_t sent_bytes = 0;
	uint8_t recv_bytes = 0;

	uint8_t send_buff[DATA_BUFFER_SIZE];
	uint8_t recv_buff[DATA_BUFFER_SIZE];
	uint8_t column;
	uint8_t row;
	uint8_t limit = 0;
	uint8_t rec_status;
	uint8_t send_status;


	//define circles in big array
	for(int i = 0; i < LED_MATRIX_COLS; i++) {
		for ( int j = 0; j < LED_MATRIX_ROWS; j++) {
			array[i][j].status = 0;
			array[i][j].x = 136 + i * 53;
			array[i][j].y = 27 + j * 53;
			//BSP_LCD_FillCircle(array[i][j].x, array[i][j].y, 17);
		}
	}

	clear_table();
	fill_field();

	while (limit < 13) {
		while (connected != 0) {
			connected = connect(client_socket, (struct sockaddr *)&addr_in, sizeof(addr_in));
			osDelay(1000);
		}

		BSP_TS_GetState(ts_state_ptr);
		if (ts_state.touchDetected) {
			if(ts_state_ptr->touchX[0] > 108) {

				column = (ts_state_ptr->touchX[0] - FIRST_SQUARE) / SQUARE_SIDE;
				row = ts_state_ptr->touchY[0] / SQUARE_SIDE;

				send_buff[0] = column;
				send_buff[1] = row;
				sent_bytes = send(client_socket, send_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
				recv(client_socket, &rec_status, sizeof(uint8_t), 0);
				if (rec_status == 1) {
					BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 20);
					limit++;
				} else if (rec_status == 0) {
					BSP_LCD_SetTextColor(LCD_COLOR_RED);+
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 20);
				}
				recv(client_socket, recv_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
				send_status = led_matrix_state[recv_buff[1]][recv_buff[0]];
				send(client_socket, &send_status, sizeof(uint8_t), 0);
				if(send_status == 1) {
//					BSP_LCD_SetTextColor(LCD_COLOR_RED);
//					BSP_LCD_FillCircle(small_array[recv_buff[0]][recv_buff[1]].x, small_array[recv_buff[0]][recv_buff[1]].y, 8);
//					small_array[recv_buff[0]][recv_buff[1]].status = 2;
					led_matrix_set(recv_buff[1], recv_buff[0], 0);
				}
				osDelay(300);
			}//if touch on field

		}//touch_detect
	}//while
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(150, 150, (uint8_t *)"YOU WON!!!", LEFT_MODE);
	closesocket(client_socket);
}//client thread



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

		// Iterate through every column or row
		for(int i = 0; i < LED_MATRIX_COLS; i++) {
			for (int j = 0; j < LED_MATRIX_ROWS; j++) {

				// Wait for the mutex
				osMutexWait(led_matrix_mutex_id, osWaitForever);
				// Turn on the leds in that column or row
				HAL_GPIO_WritePin(row[j].gpio_port, row[j].pin_num, led_matrix_state[j][i]);

				// Release the mutex column[j].pin_num
				osMutexRelease(led_matrix_mutex_id);
			}
			//column down
			HAL_GPIO_WritePin(column[i].gpio_port, column[i].pin_num, 0);
			osDelay(1);
			//column up
			HAL_GPIO_WritePin(column[i].gpio_port, column[i].pin_num, 1);

		}//draw

	}//while


	// Terminating thread
	while (1) {
		LCD_ErrLog("led_matrix - terminating...\n");
		osThreadTerminate(NULL);
	}
}//matrix thread



void clear_table()
{
	BSP_LCD_Clear(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_FillRect(10, 10, 80, 50);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_DisplayStringAt(11, 30, (uint8_t *)"SHIPS READY", LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	//BSP_LCD_DrawHLine(0, 0, 479);
	for (int x = 107; x < 470; x += 53) {
		for(int y = 1; y < 250; y += 53) {
			BSP_LCD_DrawRect(x, y, 53, 53);
		}//for y
	}//for x
}//function

/*
void draw_small_table()
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for (int x = 3; x < 135; x += 22) {
		for(int y = 136; y < 267; y += 22) {
			BSP_LCD_DrawRect(x, y, 22, 22);
		}//for y
	}//for x
}//function
*/

void fill_field()
{
	uint8_t limit = 13;
	uint8_t column;
	uint8_t row;
	while (1) {

		BSP_TS_GetState(ts_state_ptr);
		if (ts_state.touchDetected) {

			if (ts_state_ptr->touchX[0] > 10 &&
				ts_state_ptr->touchX[0] < 90 &&
				ts_state_ptr->touchY[0] > 10 &&
				ts_state_ptr->touchY[0] < 60 &&
				limit == 0) {
				break;
			}

			if (ts_state_ptr->touchX[0] > 108) {
				column = (ts_state_ptr->touchX[0] - 108) / 54;
				row = ts_state_ptr->touchY[0] / 54;
				if (array[column][row].status == 0) {
					array[column][row].status = 1;
					BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 20);
					led_matrix_set(row, column, array[column][row].status);
					limit--;
				} else if (array[column][row].status == 1) {
					array[column][row].status = 0;
					BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 20);
					led_matrix_set(row, column, array[column][row].status);
					limit++;
				}
			}//where
			osDelay(600);
		}//touch detect

	}//while

	//fill small array
	clear_table();
/*
	draw_small_table();
	for(int i = 0; i < LED_MATRIX_ROWS; i++) {
		for (int j = 0; j < LED_MATRIX_COLS; j++) {
			small_array[i][j].status = 0;
			small_array[i][j].x = 14 + i * 22;
			small_array[i][j].y = 147 + j * 22;
			if (array[i][j].status == 1) {
				small_array[i][j].status = 1;
				BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
				BSP_LCD_FillCircle(small_array[i][j].x, small_array[i][j].y, 8);
			}
		}//for j
	}//for i
*/
	//reset the big array
	for(int i = 0; i < LED_MATRIX_COLS; i++) {
		for ( int j = 0; j < LED_MATRIX_ROWS; j++) {
			array[i][j].status = 0;
		}
	}
}//function


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

void led_matrix_set(uint8_t row, uint8_t col, uint8_t state)
{
	// TODO:
	// Wait for the mutex
	osMutexWait(led_matrix_mutex_id, osWaitForever);
	// TODO:
	// Change the LED in the selected row and col to the specified state
	// Use the led_matrix_state 2D array variable!
	led_matrix_state [row][col] = state;
	// TODO:
	// Release the mutex
	osMutexRelease(led_matrix_mutex_id);
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
