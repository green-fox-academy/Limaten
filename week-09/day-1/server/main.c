#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Create Server and Client Applications that send and receive messages.

//#pragma comment(lib, "ws2_32.lib")


int main()
{
    // winstock init
    WSADATA ws_data;
    int ver = MAKEWORD(2, 2);
    int wstart = WSAStartup(ver, &ws_data);
    if (wstart != 0) {
        printf("Server: WSAStartup failed with error %ld\n", WSAGetLastError());
        return -1;
    }

    //create socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listening == INVALID_SOCKET) {
        printf("Server: Error at socket(), error code: %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    // bind the socket
    SOCKADDR_IN hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(5150);
    hint.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listening, (SOCKADDR*)&hint, sizeof(hint)) == SOCKET_ERROR) {
        printf("Server: bind() failed! Error code: %ld.\n", WSAGetLastError());
        closesocket(listening);
        WSACleanup();
        return -1;
    }


    //wait for connection
    SOCKADDR_IN client;
//    int client_size = sizeof(client);
    SOCKET client_socket;// = accept(listening, (SOCKADDR*)&client, &client_size);


    if (listen(listening, 5) == SOCKET_ERROR) {
        printf("Server: listen(): Error listening on socket %ld.\n", WSAGetLastError());
        closesocket(listening);
        WSACleanup();
        return -1;
    }
/*
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];


    if (getnameinfo((SOCKADDR*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
        printf("Connected on port! %s \n", host);
    }
*/

    char buff[4096];
    //infitiny loop
    while (1) {
        ZeroMemory(buff, 4096);
        client_socket = SOCKET_ERROR;
        int bytes_recv;

        printf("here1!\n");
        client_socket = accept(listening, NULL, NULL);
        printf("here2!\n");
        printf("Server: accept() is OK...\n");
        printf("Server: Client connected, ready for receiving and sending data...\n");

        do {


            //get data
            printf("waiting for recv\n");
            bytes_recv = recv(client_socket, buff, 4096, 0);
            if (bytes_recv == SOCKET_ERROR) {
                printf("Server: receive() failed? Error code: %ld.\n", WSAGetLastError());
                break;
            }
            if (bytes_recv == 0) {
                printf("Client disconnected\n");
                break;
            }

            //echo message back
            printf("sending back (echo)\n");
            send(client_socket, buff, bytes_recv + 1, 0);

        } while (bytes_recv > 0) ;

        closesocket(client_socket);
        printf("client sokcet closed!!!\n");


    //cleanup
    if(WSACleanup() != 0)
          printf("Server: WSACleanup() failed! Error code: %ld\n", WSAGetLastError());
     else
          printf("Server: WSACleanup() is OK...\n");

    return 0;
    }
}
