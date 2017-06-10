#ifndef TEMP_LOG_H_INCLUDED
#define TEMP_LOG_H_INCLUDED
#define BUFF_SIZE 26

struct circ_buff {
    char buffer[BUFF_SIZE];
    char *head;
    uint8_t *tail;
    uint8_t *write_ptr;
    uint8_t *read_ptr;
}buffer;

void menu();
void print_com();
void exit_program();
void open_port();
void close_port();
void get_data();
void buffer_init();

#endif // TEMP_LOG_H_INCLUDED
