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
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define SERVER_IP           "10.27.6.226"
#define SERVER_PORT        	5656
#define DATA_BUFFER_SIZE    5
// X, Y, COLOR, RADIUS
#define RADIUS				4
/* Private variables ---------------------------------------------------------*/
TS_StateTypeDef ts_state;
TS_StateTypeDef *ts_state_ptr = &ts_state;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_client_thread(void const *argument)
{
	osDelay(5000);
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(SERVER_PORT);
	addr_in.sin_addr.s_addr = inet_addr(SERVER_IP);

	int8_t connected = -1;
	uint8_t sent_bytes = -1;

	uint32_t buff[DATA_BUFFER_SIZE];
	buff[2] = LCD_COLOR_DARKMAGENTA;
	buff[3] = RADIUS;
	buff[4] = LCD_COLOR_MAGENTA;
	while (1) {
		while (connected != 0 ) {
			connected = connect(client_socket, (struct sockaddr *)&addr_in, sizeof(addr_in));
			osDelay(1000);
		}

		do {
			if(BSP_PB_GetState(BUTTON_KEY))
				BSP_LCD_Clear(LCD_COLOR_MAGENTA);
			BSP_TS_GetState(ts_state_ptr);
			if (ts_state.touchDetected) {
				// Draw
				if (ts_state_ptr->touchX[0] < 420 - RADIUS	&&
					ts_state_ptr->touchX[0] > RADIUS		&&
					ts_state_ptr->touchY[0] < 272 - RADIUS	&&
					ts_state_ptr->touchY[0] > RADIUS) {
					BSP_LCD_SelectLayer(0);
					BSP_LCD_FillCircle(ts_state_ptr->touchX[0], ts_state_ptr->touchY[0], RADIUS);
					buff[0] = (uint32_t)ts_state_ptr->touchX[0];
					buff[1] = (uint32_t)ts_state_ptr->touchY[0];
					sent_bytes = send(client_socket, buff, DATA_BUFFER_SIZE * sizeof(uint32_t), 0);
				}
			}//touch_detect
		} while (sent_bytes > 0);
		closesocket(client_socket);
	}//while
}//thread

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
