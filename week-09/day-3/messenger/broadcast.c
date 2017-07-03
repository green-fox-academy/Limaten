#include "broadcast.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

void thread_broadcast()
{
    char buff[30];
    char s[2] = " ";
    SOCKET bc_server;
    bc_server = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(BC_SERVER_PORT);
	addr_in.sin_addr.s_addr = INADDR_ANY;
	struct sockaddr *addr = (struct sockaddr *)&addr_in;

    struct sockaddr_in their_addr;
    int their_length = sizeof(their_addr);

    if (bind(bc_server,(struct sockaddr*) &addr_in, sizeof(struct sockaddr)) == -1)
        printf("bc srv bind nem jo\n");

    while (1) {
        if (recvfrom(bc_server, buff, sizeof(buff), 0, (struct sockaddr*) &their_addr, &their_length) == -1)
            printf("bc srv recv nem jo\n");
        printf("from: %s\tbc rcv msg: %s\n", inet_ntoa(their_addr.sin_addr), buff);
        char *send_disc_port = strtok(buff, s);
        send_disc_port = strtok(NULL, s);
        printf("bc_port: %d\n", atoi(send_disc_port));
        send_disc(atoi(send_disc_port), inet_ntoa(their_addr.sin_addr));
        memset(buff,0,strlen(buff));
    }
}
