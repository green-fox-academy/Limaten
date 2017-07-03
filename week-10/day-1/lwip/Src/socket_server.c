/* Includes ------------------------------------------------------------------*/

#include "socket_server.h"
#include "lcd_log.h"
#include "cmsis_os.h"
#include "app_ethernet.h"
#include "lwip/sockets.h"

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
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(24862);
	addr_in.sin_addr.s_addr = INADDR_ANY;
	struct sockaddr *addr = (struct sockaddr *)&addr_in;

	int master_sock = socket(PF_INET, SOCK_STREAM, 0);
	bind(master_sock, addr, sizeof(*addr));
	listen(master_sock, 1);
	struct sockaddr client_addr;
	int slave_sock;
	char buff[1024];

	while (1) {
		slave_sock = accept(master_sock, &client_addr, NULL);
		LCD_UsrLog("accept ok\n");
		int received_bytes;
		do {
			received_bytes = recv(slave_sock, buff, 1024, 0);
			buff[received_bytes] = '\0';
			LCD_UsrLog("<USER> %s\n", buff);
			send(slave_sock, buff, received_bytes, 0);
		} while (received_bytes > 0);
		closesocket(slave_sock);
	}//while
	closesocket(master_sock);
}//function


void broadcast_server_thread(void const *argument)
{
	char buff[30];
	char s[2] = " ";
	int bc_server;
	bc_server = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(12345);
	addr_in.sin_addr.s_addr = INADDR_ANY;
	struct sockaddr *addr = (struct sockaddr *)&addr_in;

	struct sockaddr_in their_addr;
	int their_length = sizeof(their_addr);

	bind(bc_server, (struct sockaddr *)&addr_in, sizeof(struct sockaddr));

	while (1) {
		recvfrom(bc_server, buff, sizeof(buff), 0, (struct sockaddr*)&their_addr, &their_length);
		LCD_UsrLog("ip: %s    ", inet_ntoa(their_addr.sin_addr));
		char *send_disc_port = strtok(buff, s);
		send_disc_port = strtok(NULL, s);
		LCD_UsrLog("port: %d\n", atoi(send_disc_port));
        memset(buff,0,strlen(buff));
	}//while
}//function
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
