/* Includes ------------------------------------------------------------------*/
#include "main.h"
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
#define SERVER_IP 			"10.27.6.142"
#define DATA_BUFFER_SIZE 	2
#define ROW 				6
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef srv_ts_state;
TS_StateTypeDef *srv_ts_state_ptr = &srv_ts_state;
struct field array[6][6];
struct field small_array[6][6];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void srv_clear_table();
void srv_draw_small_table();
void srv_fill_field();

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	while (is_ip_ok() == 0) {
		osDelay(500);
	}
	int master_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(24862);
	addr_in.sin_addr.s_addr = INADDR_ANY;
	struct sockaddr *addr = (struct sockaddr *)&addr_in;


	bind(master_sock, addr, sizeof(*addr));
	listen(master_sock, 1);
	struct sockaddr client_addr;
	int slave_sock = -1;

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

	for(int i = 0; i < 6; i++) {
		for ( int j = 0; j < 6; j++) {
			array[i][j].status = 0;
			array[i][j].x = 231 + i * 45;
			array[i][j].y = 23 + j * 45;
			//BSP_LCD_FillCircle(array[i][j].x, array[i][j].y, 17);
		}
	}

	srv_clear_table();
	srv_fill_field();

	while (1) {
		while (slave_sock == -1) {
			slave_sock = accept(master_sock, &client_addr, NULL);
			osDelay(1000);
		}

		//LCD_UsrLog("accept ok\n");
		int received_bytes = 0;
		do {
			recv(slave_sock, recv_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
			send_status = small_array[recv_buff[0]][recv_buff[1]].status;
			send(slave_sock, &send_status, sizeof(uint8_t), 0);
			if(small_array[recv_buff[0]][recv_buff[1]].status == 1) {
				BSP_LCD_SetTextColor(LCD_COLOR_RED);
				BSP_LCD_FillCircle(small_array[recv_buff[0]][recv_buff[1]].x, small_array[recv_buff[0]][recv_buff[1]].y, 8);
				small_array[recv_buff[0]][recv_buff[1]].status = 2;
			}
			BSP_TS_GetState(srv_ts_state_ptr);
			while (srv_ts_state.touchDetected == 0) {
				BSP_TS_GetState(srv_ts_state_ptr);
			}
			if (srv_ts_state.touchDetected) {
				if(srv_ts_state_ptr->touchX[0] > 208) {
					column = (srv_ts_state_ptr->touchX[0] - 208) / 46;
					row = srv_ts_state_ptr->touchY[0] / 46;
					send_buff[0] = column;
					send_buff[1] = row;
					sent_bytes = send(slave_sock, send_buff, DATA_BUFFER_SIZE * sizeof(uint8_t), 0);
					received_bytes = recv(slave_sock, &rec_status, sizeof(uint8_t), 0);
					if (rec_status == 1) {
						BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
						BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
						limit++;
					} else if (rec_status == 0) {
						BSP_LCD_SetTextColor(LCD_COLOR_RED);
						BSP_LCD_FillCircle(array[column][row].x, array[column][row].y, 17);
					}

					osDelay(600);
				}//if touch on field

			}//touch_detect

		} while (received_bytes > 0);
		closesocket(slave_sock);
	}//while
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(150, 150, (uint8_t *)"YOU WON!!!", LEFT_MODE);
	closesocket(master_sock);
}//thread


void srv_clear_table()
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

void srv_draw_small_table()
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	for (int x = 3; x < 135; x += 22) {
		for(int y = 136; y < 267; y += 22) {
			BSP_LCD_DrawRect(x, y, 22, 22);
		}//for y
	}//for x
}//function


void srv_fill_field()
{
	uint8_t limit = 13;
	uint8_t column;
	uint8_t row;
	while (1) {
		BSP_TS_GetState(srv_ts_state_ptr);
		if (srv_ts_state.touchDetected) {
			if (srv_ts_state_ptr->touchX[0] > 10 &&
				srv_ts_state_ptr->touchX[0] < 90 &&
				srv_ts_state_ptr->touchY[0] > 10 &&
				srv_ts_state_ptr->touchY[0] < 60 &&
				limit == 0) {
				break;
			}
			if (srv_ts_state_ptr->touchX[0] > 208) {
				column = (srv_ts_state_ptr->touchX[0] - 208) / 46;
				row = srv_ts_state_ptr->touchY[0] / 46;
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
	srv_clear_table();
	srv_draw_small_table();
	for(int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			small_array[i][j].status = 0;
			small_array[i][j].x = 14 + i * 22;
			small_array[i][j].y = 146 + j * 22;
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
