#include "send.h"
#include "mainh.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

SOCKET client_socket_tcp;

void handle_error_send(const char *error_string)
{
	printf("Error: %s\nError code: %d\n", error_string, WSAGetLastError());
	WSACleanup();
	printf("Press any key to exit from the program...");
	while (!kbhit());
	exit(EXIT_FAILURE);
}

void connect_to_server(SOCKET *client_sock, unsigned int server_port, char *server_ip)
{
    printf("itt a baj1?\n");
	// Creating client socket
	(*client_sock) = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock < 0)
		handle_error_send("socket() ");
	// Creating server address
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(server_port);
	addr_in.sin_addr.s_addr = inet_addr(server_ip);
	// Connecting the client socket to the server
	int connect_retval = connect(*client_sock, (struct sockaddr *)&addr_in, sizeof(addr_in));
	if (connect_retval < 0)
		handle_error_send("connect() ");
}

int send_message(SOCKET *socket)
{
	// Get the message from the user
	char msg[DATA_BUFFER_SIZE];
    gets(msg);
	// Send the message to the servers
	int sent_bytes = send(*socket, msg, strlen(msg), 0);
	if (sent_bytes < 0)
		handle_error_send("send() ");

	return sent_bytes;
}

void send_req()
{
    int var = 1;
    SOCKET client_socket_udp;
    client_socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(client_socket_udp, SOL_SOCKET, SO_BROADCAST, &var, sizeof(var));
    char *broadcast_msg;
    broadcast_msg = "TOTORO 24862";
    struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(12345);
	addr_in.sin_addr.s_addr = INADDR_BROADCAST;
    int asd = sendto(client_socket_udp, broadcast_msg, strlen(broadcast_msg), 0, (struct sockaddr *)&addr_in, sizeof(addr_in));
    close(client_socket_udp);
    printf("disc req sent\n");
}

void send_disc(int port, char *ip)
{
    //connect funct here

    char *disc_msg;
    disc_msg = "Mate 24861";
    int sent_bytes;
    sent_bytes = send(client_socket_tcp, disc_msg, strlen(disc_msg), 0);
    if (sent_bytes != 0)
        printf("sent went wrong\n");
    closesocket(client_socket_tcp);
}
