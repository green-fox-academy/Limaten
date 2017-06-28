#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//#pragma comment(lib, "ws2_32.lib")

int main()
{
    char *ip_adress = "127.0.0.1";
    int port = 5150;
    WSADATA wsdata;
    SOCKET sending_socket;
    SOCKADDR_IN server_address;
    int ret_code;

    WSAStartup(MAKEWORD(2,2), &wsdata);
    printf("Client: Winsock DLL status is %s.\n", wsdata.szSystemStatus);


    sending_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sending_socket == INVALID_SOCKET) {
        printf("Client: socket() failed! Error code: %ld\n", WSAGetLastError());
        // Do the clean up
        WSACleanup();
        // Exit with error
        return -1;
    } else
        printf("Client: socket() is OK!\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5150);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret_code = connect(sending_socket, (SOCKADDR*)&server_address, sizeof(server_address));

    printf("Client: connect() is OK!\nrdy for send and receive\n");

    char send_buff[4096];
    char recv_buff[4096];
    while(1) {
        ret_code = connect(sending_socket, (SOCKADDR*)&server_address, sizeof(server_address));
        if (ret_code) {
            printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
            closesocket(sending_socket);
            WSACleanup();
            return -1;
        }

        printf(">");
        ZeroMemory(send_buff, 4096);
        ZeroMemory(recv_buff, 4096);
        gets(send_buff);

        int send_result = send(sending_socket, send_buff, 4096, 0);
        if (send_result != SOCKET_ERROR) {
            int bytes_recv = recv(sending_socket, recv_buff, 4096, 0);
            if (bytes_recv > 0)
                printf("<SERVER> %s\n", recv_buff);
        }

    }


    if(closesocket(sending_socket) != 0)
        printf("Client: Cannot close \"SendingSocket\" socket. Error code: %ld\n", WSAGetLastError());
    else
        printf("Client: Closing \"SendingSocket\" socket...\n");

    if(WSACleanup() != 0)
        printf("Client: WSACleanup() failed!...\n");
    else
        printf("Client: WSACleanup() is OK...\n");

    return 0;
}
