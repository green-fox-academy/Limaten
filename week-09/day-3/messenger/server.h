#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <conio.h>
#include <math.h>

#define SERVER_PORT         24861
#define DATA_BUFFER_SIZE    1024
#define QUEUE_SIZE 1

void thread_server();

#endif // _SERVER_H_
