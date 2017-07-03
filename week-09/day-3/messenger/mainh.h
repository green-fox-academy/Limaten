#ifndef _MAINH_H_
#define _MAINH_H_

#include <stdint.h>
#include <stdio.h>


//print menu
void print_menu();

//print online users
void print_users();
//online users struct

struct users_online {
    uint32_t ip_address;
    int port;
    char name[30];
};

int number_users;
struct users_online users[50];

#endif // _MAINH_H_
