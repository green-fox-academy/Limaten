#ifndef _SEND_H_
#define _SEND_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

#define DATA_BUFFER_SIZE    1024

#define QUEUE_SIZE 1

void handle_error_send(const char *error_string);

void connect_to_server(SOCKET *client_sock, unsigned int server_port, char *server_ip);

int send_message(SOCKET *socket);

void send_req();

void send_disc(int port, char *ip);
/*
void thread_send()
{

	// Connect to server
	connect_to_server(&client_socket_tcp, SERVER_PORT, SERVER_IP);

	// Local variables used in the do-while loop
	int sent_bytes;
	int received_bytes;
	char recv_buff[DATA_BUFFER_SIZE];
    // Send data to the server
    sent_bytes = send_message(&client_socket_tcp);
    // Receive the answer if message was sent
    if (sent_bytes > 0) {
        received_bytes = recv(client_socket_tcp, recv_buff, DATA_BUFFER_SIZE, 0);
        // Error handling
        if (received_bytes < 0) {
            handle_error("recv() ");
        } else {
            // Printing out received string
            recv_buff[received_bytes] = '\0';
            printf("<SERVER> %s\n", recv_buff);
        }
    }

//	printf("Closing the socket...\n");
	closesocket(client_socket_tcp);
}
*/
#endif // _SERVER_H_
