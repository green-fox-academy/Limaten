#define SERVER_IP           "127.0.0.1"
#define SERVER_PORT         55555
#define DATA_BUFFER_SIZE    1024
#define _WIN32_WINNT 0x0501
#define QUEUE_SIZE 1

void handle_error(const char *error_string)
{
	printf("Error: %s\nError code: %d\n", error_string, WSAGetLastError());
	WSACleanup();
	printf("Press any key to exit from the program...");
	while (!kbhit());
	exit(EXIT_FAILURE);
}

void wsa_init()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		handle_error("WSAStartup() ");
}

void connect_to_server(SOCKET *client_sock, unsigned int server_ip, char *server_port)
{
	// Creating client socket
	(*client_sock) = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (client_sock < 0)
		handle_error("socket() ");

	// Creating server address
	struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(server_port);
	addr_in.sin_addr.s_addr = inet_addr(server_ip);

	// Connecting the client socket to the server
	int connect_retval = connect(*client_sock, (struct sockaddr *)&addr_in, sizeof(addr_in));
	if (connect_retval < 0)
		handle_error("connect() ");

	printf("Connected to %s:%d\n", SERVER_IP, SERVER_PORT);
}

int send_message(SOCKET *socket)
{
	// Get the message from the user
	char msg[DATA_BUFFER_SIZE];
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t<YOU> ");
	gets(msg);
	// Send the message to the servers
	int sent_bytes = send(*socket, msg, strlen(msg), 0);
	if (sent_bytes < 0)
		handle_error("send() ");

	return sent_bytes;
}
