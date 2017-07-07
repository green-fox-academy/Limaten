/* Includes ------------------------------------------------------------------*/
#include "socket_client.h"
#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"
#include "stm32746g_discovery_ts.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
struct field {
	uint8_t status; // 0 = water | 1 = ship | 2 = X (hit ship)
	uint16_t x;
	uint16_t y;
};
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SERVER_PORT 		24862
#define SERVER_IP 			"10.27.6.187"
#define DATA_BUFFER_SIZE 	2
#define ROW 				6
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef ts_state;
TS_StateTypeDef *ts_state_ptr = &ts_state;
struct field array[6][6];
struct field small_array[6][6];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void clear_table();
void draw_small_table();
void fill_field();

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
	for(int i = 0; i < 6; i++) {
		for ( int j = 0; j < 6; j++) {
			array[i][j].status = 0;
			array[i][j].x = 231 + i * 45;
			array[i][j].y = 23 + j * 45;
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
			if(ts_state_ptr->touchX[0] > 208) {
				column = (ts_state_ptr->touchX[0] - 208) / 46;
				row = ts_state_ptr->touchY[0] / 46;
				send_buff[0] = column;
				send_buff[1] = row;
				sent_bytes = send(client_socket, send_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
				recv(client_socket, &rec_status, sizeof(uint8_t), 0);
				if (rec_status == 1) {
					BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
					limit++;
				} else if (rec_status == 0) {
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
				}
				recv(client_socket, recv_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
				send_status = small_array[recv_buff[0]][recv_buff[1]].status;
				send(client_socket, &send_status, sizeof(uint8_t), 0);
				if(small_array[recv_buff[0]][recv_buff[1]].status == 1) {
					BSP_LCD_SetTextColor(LCD_COLOR_RED);
					BSP_LCD_FillCircle(small_array[recv_buff[0]][recv_buff[1]].x, small_array[recv_buff[0]][recv_buff[1]].y, 8);
					small_array[recv_buff[0]][recv_buff[1]].status = 2;
				}
				osDelay(600);
			}//if touch on field

		}//touch_detect
	}//while
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(150, 150, (uint8_t *)"YOU WON!!!", LEFT_MODE);
	closesocket(client_socket);
}//thread


void clear_table()
{
	BSP_LCD_Clear(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_FillRect(10, 10, 80, 50);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_DisplayStringAt(11, 30, (uint8_t *)"SHIPS READY", LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DrawHLine(0, 0, 479);
	for (int x = 209; x < 475; x += 45) {
		for(int y = 1; y < 267; y += 45) {
			BSP_LCD_DrawRect(x, y, 45, 45);
		}//for y
	}//for x
}//function

void draw_small_table()
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for (int x = 3; x < 135; x += 22) {
		for(int y = 136; y < 267; y += 22) {
			BSP_LCD_DrawRect(x, y, 22, 22);
		}//for y
	}//for x
}//function


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
			if (ts_state_ptr->touchX[0] > 208) {
				column = (ts_state_ptr->touchX[0] - 208) / 46;
				row = ts_state_ptr->touchY[0] / 46;
				if (array[column][row].status == 0) {
					array[column][row].status = 1;
					BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
					limit--;
				} else if (array[column][row].status == 1) {
					array[column][row].status = 0;
					BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
					BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
					limit++;
				}
			}//where
			osDelay(600);
		}//touch detect
	}//while

	//fill small array
	clear_table();
	draw_small_table();
	for(int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
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

	//reset the big array
	for(int i = 0; i < 6; i++) {
		for ( int j = 0; j < 6; j++) {
			array[i][j].status = 0;
		}
	}
}//function
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
