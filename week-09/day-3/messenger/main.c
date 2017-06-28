#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

#include "send.h"
#include "server.h"
#include "broadcast.h"
#include "main.h"

#define SERVER_IP           "127.0.0.1"
#define SERVER_PORT         55555
#define DATA_BUFFER_SIZE    1024
#define _WIN32_WINNT 0x0501
#define QUEUE_SIZE 1


int main()
{
    struct users_online users[50];
    print_menu();
    //
    _beginthread(thread_server, 0, NULL);
    _beginthread(thread_broadcast, 0, NULL);
	// Initialize the WSA
	wsa_init();

	// Connect to server
	SOCKET client_socket;
	connect_to_server(&client_socket, SERVER_IP, SERVER_PORT);

	// Local variables used in the do-while loop
	int sent_bytes;
	int received_bytes;
	char recv_buff[DATA_BUFFER_SIZE];
	do {
		// Send data to the server
		sent_bytes = send_message(&client_socket);
		// Receive the answer if message was sent
		if (sent_bytes > 0) {
			received_bytes = recv(client_socket, recv_buff, DATA_BUFFER_SIZE, 0);
			// Error handling
			if (received_bytes < 0) {
				handle_error("recv() ");
			} else {
				// Printing out received string
				recv_buff[received_bytes] = '\0';
				printf("<SERVER> %s\n", recv_buff);
			}
		}
	} while (sent_bytes > 0);

	printf("Closing the socket...\n");
	closesocket(client_socket);
	printf("Cleaning up memory...\n");
	WSACleanup();
	return 0;

}//main
