#include "server.h"
#include "mainh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

void thread_server()
{

	// Server address structure initialization
	struct sockaddr_in addr_in;                                 // Inet address structure definition
	addr_in.sin_family = AF_INET;                               // This address is an internet address
	addr_in.sin_port = htons(SERVER_PORT);                      // Server port
	addr_in.sin_addr.s_addr = INADDR_ANY;                       // Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in;        // Make a struct sockaddr pointer, which points to the address stucture

	// Creating the socket
	SOCKET master_sock = socket(AF_INET, SOCK_STREAM, 0);
	// Check if socket is ok

	// Start binding the socket to the previously set address
	bind(master_sock, addr, sizeof(*addr));
	// Check if the binding is ok

	// Start listening on with the set socket with a predefined queue size
	listen(master_sock, QUEUE_SIZE);
	// Check is listening is ok


	printf("Server is initialized, waiting for connections at port %d\n", SERVER_PORT);

	// Create variables which will be used in the while loop
	struct sockaddr client_addr;    // Client address structure
	SOCKET slave_sock;              // Slave socket definition, this will be used to store the incoming socket
	char buff[DATA_BUFFER_SIZE];                // Buffer for incoming and outgoing data
	int cntr = 1;                   // Counter for incoming connections
	while (1) {
		// Accept the connection and save the incoming socket
		slave_sock = accept(master_sock, &client_addr, NULL);
		// Check if the socket is valid
		if (slave_sock < 0)
			handle_error("accept()");

		// Receive the data sent by the client
		int received_bytes;
        received_bytes = recv(slave_sock, buff, DATA_BUFFER_SIZE, 0);
        if (received_bytes == 0) {
            printf("Connection closed, waiting for an other connection!\n");
        } else if (received_bytes == SOCKET_ERROR) {
            printf("Something went wrong with the client socket, trying to close it...\n");
            break;
        } else {
            // Print out the received data
            printf("Received string: %s \n", buff);
        }
		closesocket(slave_sock);
	}//while

	// Cleaning up used memory
	printf("Closing server socket\n");
	closesocket(master_sock);
}
