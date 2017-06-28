#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>

/* Client.c */

void thread_broadcast()
{
   char buf[512];
   int clientToServer_socket;
   unsigned int fromLength;
   struct sockaddr_in Remote_Address, Server_Address;
   struct hostent *hostPointer;
   int message, checkCall;
   int counter1 = 0;
   int counter2 = 0;
   int broadcastOn = 1;
   int broadcastOff = 0;
   char *broadcastMessage;
/*
   broadcastMessage = "Hello";

   printf("Message %s\n", broadcastMessage);
*/
   /*Create client socket*/
   clientToServer_socket=socket(AF_INET, SOCK_DGRAM, 0);
   if (clientToServer_socket==-1)
    perror("Error: client socket not created");

   /*Fill in client's sockaddr_in */
   bzero(&Remote_Address, sizeof(Remote_Address));
   Remote_Address.sin_family=AF_INET;
   hostPointer=gethostbyname(255.255.255.255);
   memcpy((unsigned char * ) &Remote_Address.sin_addr, (unsigned char *) hostPointer -> h_addr, hostPointer -> h_length);
   Remote_Address.sin_port=htons(atoi(12345);

   checkCall = setsockopt(clientToServer_socket, SOL_SOCKET, SO_BROADCAST, &broadcastOn, 4);
   if(checkCall == -1)
    perror("Error: setsockopt call failed");

   Remote_Address.sin_addr.s_addr|=htonl(0x1ff);

   checkCall = setsockopt(clientToServer_socket, SOL_SOCKET, SO_BROADCAST, &broadcastOff, 4);
   if(checkCall == -1)
    perror("Error: Second setsockopt call failed");

   int broadcastMessageLen = strlen(broadcastMessage) + 1;

   printf("Message test %d\n", broadcastMessageLen);


   message = sendto(clientToServer_socket, broadcastMessage, broadcastMessageLen, 0, (struct sockaddr *) &Remote_Address, sizeof(Remote_Address));
   if (message ==-1)
    perror("Error: sendto call failed");

   while(1)
   {
      fromLength = sizeof(Server_Address);
      message = recvfrom(clientToServer_socket, buf, 512, 0, (struct sockaddr *) &Server_Address, &fromLength);
      if (message ==-1)
     perror("Error: recvfrom call failed");

      printf("SERVER: read %d bytes from IP %s(%s)\n", message, inet_ntoa(Server_Address.sin_addr), buf);
   }
   close(clientToServer_socket);

}
