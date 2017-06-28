#define SERVER_IP           "127.0.0.1"
#define SERVER_PORT         55555
#define DATA_BUFFER_SIZE    1024
#define _WIN32_WINNT 0x0501
#define QUEUE_SIZE 1

void thread_server()
{
    WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	// Server address structure initialization
	struct sockaddr_in addr_in;                                 // Inet address structure definition
	addr_in.sin_family = AF_INET;                               // This address is an internet address
	addr_in.sin_port = htons(SERVER_PORT);                      // Server port
	addr_in.sin_addr.s_addr = inet_addr(SERVER_IP);             // Server IP
	struct sockaddr *addr = (struct sockaddr *)&addr_in;        // Make a struct sockaddr pointer, which points to the address stucture

	// Creating the socket
	SOCKET master_sock = socket(PF_INET, SOCK_STREAM, 0);
	// Check if socket is ok
	if (master_sock < 0)
		handle_error("socket() ");

	// Start binding the socket to the previously set address
	int flag = bind(master_sock, addr, sizeof(*addr));
	// Check if the binding is ok
	if (flag < 0)
		handle_error("bind() ");

	// Start listening on with the set socket with a predefined queue size
	flag = listen(master_sock, QUEUE_SIZE);
	// Check is listening is ok
	if (flag < 0)
		handle_error("listen() ");

	printf("Server is initialized, waiting for connections at %s:%d\n", SERVER_IP, SERVER_PORT);

	// Create variables which will be used in the while loop
	struct sockaddr client_addr;    // Client address structure
	SOCKET slave_sock;              // Slave socket definition, this will be used to store the incoming socket
	char buff[DATA_BUFFER_SIZE];                // Buffer for incoming and outgoing data
	int cntr = 1;                   // Counter for incoming connections
	while (!kbhit()) {
		// Accept the connection and save the incoming socket
		slave_sock = accept(master_sock, &client_addr, NULL);
		// Check if the socket is valid
		if (slave_sock < 0)
			handle_error("accept()");

		printf("%d. connection accepted\n", cntr);

		// Receive the data sent by the client
		int received_bytes;
		do {
			received_bytes = recv(slave_sock, buff, DATA_BUFFER_SIZE, 0);
			if (received_bytes == 0) {
				printf("Connection closed, waiting for an other connection!\n");
			} else if (received_bytes == SOCKET_ERROR) {
				printf("Something went wrong with the client socket, trying to close it...\n");
				break;
			} else {
				// Terminate the string with zero
				buff[received_bytes] = '\0';
				// Print out the received data
				//printf("Received string: %s \n", buff);
				// Send back the received string
				send(slave_sock, buff, received_bytes, 0);
			}
		} while (received_bytes > 0);

		closesocket(slave_sock);
		printf("%d. client socket closed\n\n", cntr);
		cntr++;
	}

	// Cleaning up used memory
	printf("Closing server socket\n");
	closesocket(master_sock);
	printf("Cleaning up WSA\n");
	WSACleanup();
	return 0;
}
