#include "send.h"
#include "server.h"
#include "broadcast.h"
#include "discovery.h"
#include "mainh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>




//extern struct users_online users[50];

void print_menu()
{
    printf(" TOTORO CHAT\n"
           " ==============================\n"
           " Commands:\n"
           " h\tDisplay this help info\n"
           " e\tExit\n"
           " n\tSet user name\n"
           " l\tList known users\n"
           " d\tSend discovery request\n"
           " m\tSend message\n\n");
}

void print_users()
{
    printf(" IP\t\tPORT\tNAME\n");
    for (int i = 0; i < number_users; i++) {
        printf(" %d\t%d\t%s\n", users[i].ip_address,
                             users[i].port,
                             users[i].name);
    }
}
