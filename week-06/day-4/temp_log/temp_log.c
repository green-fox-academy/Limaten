#include <stdlib.h>
#include <inttypes.h>
#include "temp_log.h"
#include "rs232.h"

#define BAUD 115200
#define BUFF_SIZE 26

void buffer_init()
{
    buffer.head = &buffer.buffer[0];
    buffer.tail = &buffer.buffer[BUFF_SIZE-1];
    buffer.write_ptr = buffer.head;
    buffer.read_ptr = buffer.head;
}

/*************************
 * Show the command list *
 *************************/

void print_com()
{
    printf(" ========================================\n");
    printf(" Commands:\n");
    printf("  h\tShow the command list\n");
    printf("  e\tExit from the program\n");
    printf("  l\tList available ports\n");
    printf("  p\tSet port name\n");
    printf("  w\tSet write filename\n");
    printf("  o\tOpen port\n");
    printf("  s\tStart logging / Stop logging\n");
    printf("  c\tClose port\n");
    printf("  r\tSet read filename\n");
    printf("  a\tCalculate average in given period\n");
}


/********
 * Menu *
 ********/

void menu()
{
    char command;
    command = getch();
    switch (command) {
    case 'h':
        print_com();
        break;
    case 'e':
        exit(0);
    case 'l':
        port_list();
        break;
    case 'o':
        open_port();
        break;
    case 'c':
        close_port();
        break;
    case 'd':
        get_data();
        break;
    default:
        printf(" %c is NOT a valid command\n", command);
        break;

    }
}


/************************
 * List available ports *
 ************************/

void port_list()
{
    for (int i = 0; i < comEnumerate(); i++)
        printf("%s\n", comGetPortName(i));
}


/*****************
 * Set port name *
 *****************/

void set_port_name()
{

}


/*************
 * Open port *
 *************/

void open_port()
{
    printf("\n Which port do you want to open?\n");
    char name[5];
    scanf("%s", &name);
    int port = comFindPort(name);
    if (comOpen(port,BAUD) == 1)
        printf("\n %s is open now!\n", name);
}


/**************
 * Close port *
 **************/

void close_port()
{
     printf("\n Which port do you want to close?\n");
     char name[5];
     scanf("%s", &name);
     int port = comFindPort(name);
     comClose(port);
}

void get_data()
{
    printf("\n Which port do you want to use?\n");
    char name[5];
    scanf("%s", &name);
    int port = comFindPort(name);
    printf("\n\t\t%d\n\n",comRead(port, buffer.head, BUFF_SIZE));
    for (int i = 0; i < BUFF_SIZE; i = i + 2)
        printf(" %c%c\n", buffer.buffer[i],buffer.buffer[i+1]);
}
