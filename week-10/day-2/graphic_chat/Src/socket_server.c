/* Includes ------------------------------------------------------------------*/
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
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// TODO:
// Implement this function!
void socket_server_thread(void const *argument)
{
	osDelay(2000);
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
	uint32_t buff[5];
	while (1) {
		while (slave_sock != 1) {
			slave_sock = accept(master_sock, &client_addr, NULL);
			osDelay(1000);
		}
		if(slave_sock != -1)
			LCD_UsrLog("accept ok\n");
		int received_bytes = 0;
		do {
			received_bytes = recv(slave_sock, buff, 5 * sizeof(uint32_t), 0);
			BSP_LCD_SetTextColor(buff[2]);
			BSP_LCD_FillCircle(buff[0], buff[1], buff[3]);
		} while (received_bytes > 0);
		closesocket(slave_sock);
	}//while
	closesocket(master_sock);
}//thread


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
