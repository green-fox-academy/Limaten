#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TODO.h"

int main()
{
    task *tasks = NULL;
    char comm[4];

    printf("\nToDo application\n");
    print_commands();

    while (1) {
        printf("\nEnter the command:\n");
        gets(comm);
        if (strcmp(comm, "-ex") == 0)
            return 0;
        tasks = menu(tasks, comm);
    }

    tasks = empty_list(tasks);
}
