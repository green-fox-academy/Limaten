//number of  online users
int number_users;

//online users struct
struct users_online {
    unsigned long ip_address;
    int port;
    char name[30];
};

//print menu
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

//print online users
void print_users(struct users_online *users)
{
    printf(" IP\t\tPORT\tNAME\n");
    for (int i = 0; i < number_users; i++) {
        printf(" %d\t%d\t%s\n", users[i].ip_address,
                             users[i].port,
                             users[i].name);
    }
}
