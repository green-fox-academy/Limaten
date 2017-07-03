#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

#include "send.h"
#include "server.h"
#include "broadcast.h"
#include "discovery.h"
#include "mainh.h"


int main()
{
    WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	number_users = 0;

    print_menu();

    _beginthread(thread_server, 0, NULL);
    _beginthread(thread_broadcast, 0, NULL);
    _beginthread(thread_discovery, 0, NULL);
	char command;
	while (1) {
        if (kbhit()) {
            command = getch();
            switch (command) {
            case 'h':
                print_menu();
                break;
            case 'e':
                exit(0);
                break;
            case 'n':
                break;
            case 'l':
                print_users();
                break;
            case 'd':
                send_req();
                break;
            case 'm':
                break;
            default:
                printf("Not a valid command!\n");
                break;
            }//switch
        }//if kbhit
	}//while
	WSACleanup();
	return 0;
}//main

