#include "TODO.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/***********
* Commands *
 ***********/

void print_commands()
{
    printf("====================\n");
    printf("Commands:\n");
    printf(" -a\tAdds a new task\n");
    printf(" -wr\tWrite current todos to file\n");
    printf(" -rd\tRead todos from\n");
    printf(" -l\tLists all the task\n");
    printf(" -e\tEmpty the list\n");
    printf(" -r\tRemoves a task\n");
    printf(" -c\tCompletes a task\n");
    printf(" -p\tAdd priority to a task\n");
    printf(" -lp\tLists all the task by priority\n");
    printf(" -cm\tShow commands\n");
    printf(" -ex\tClose the application\n\n");
}


/*****************
 * Adding a task *
 *****************/

task *add_task(task *tasks)
{
    int pos = 1;
    char name[256];
    printf("\nEnter the task:\n");
    gets(name);
    task *add_ptr = tasks;

    if (add_ptr == NULL) {
        add_ptr = malloc(sizeof(task));
        strcpy(add_ptr->name, name);
        add_ptr->number = pos;
        add_ptr->next = NULL;
        tasks = add_ptr;
    } else {
        pos++;
        while (add_ptr->next != NULL) {
            add_ptr = add_ptr->next;
            pos++;
        }
        add_ptr->next = malloc(sizeof(task));
        strcpy(add_ptr->next->name, name);
        add_ptr->next->number = pos;
        add_ptr->next->next = NULL;
    }
    printf("\nTask added\n");
    return tasks;
}


/****************
 * Task listing *
 ****************/

void print_tasks(task *tasks)
{
    if (tasks == NULL) {
        printf("\nNo todos for today! :)\n");
    } else {
        printf("\nList by number\n");
        printf("==============\n");
        printf("Num     | Tasks\n");
        task *print_ptr = tasks;
        while (print_ptr != NULL) {
            printf("%d\t", print_ptr->number);
            printf("- %s\n", print_ptr->name);
            print_ptr = print_ptr->next;
        }
    }

}


/*********************
 * Writing to a file *
 *********************/

void write_file(task *tasks)
{
    char tmp[50];
    printf("\nTo which file?\n");
    gets(tmp);
    FILE *file = fopen(tmp, "w");

    task *write_ptr = tasks;
    while (write_ptr != NULL) {
        fprintf(file, "%d %s\n", write_ptr->number, write_ptr->name);
        write_ptr = write_ptr->next;
    }
    fclose(file);
}


/***********************
 * Reading from a file *
 ***********************/

task *read_file(task *tasks)
{
    char tmp[50];
    printf("\nFrom which file?\n");
    gets(tmp);
    FILE *file = fopen(tmp, "r");

    char name[256];
    int number;
    task *read_ptr = tasks;

    while (fscanf(file, "%d %s\n", &number, &name) == 2) {
        if (read_ptr == NULL) {
            read_ptr = malloc(sizeof(task));
            strcpy(read_ptr->name, name);
            read_ptr->number = number;
            read_ptr->next = NULL;
            tasks = read_ptr;
        } else {
            while (read_ptr->next != NULL) {
                read_ptr = read_ptr->next;
            }
            read_ptr->next = malloc(sizeof(task));
            strcpy(read_ptr->next->name, name);
            read_ptr->next->number = number;
            read_ptr->next->next = NULL;
        }
    }
    fclose(file);
    return tasks;
}


/******************
 * Empty the list *
 ******************/
task *empty_list(task *tasks)
{
    task *free_ptr;
    while (tasks != NULL) {
        free_ptr = tasks;
        tasks = tasks->next;
        free(free_ptr);
    }
    tasks = NULL;
    return tasks;
}

/************************
 * Remove from the list *
 ************************/

task* remove_task(task *tasks)
{
    int i = 0;
    int change_number = 0;
    task *rem_ptr =  tasks;
    task *prev = NULL;

    printf("Which task you want to remove?\n");
    scanf("%d", &i);

    if (tasks == NULL) {
        printf("\nThere is NO task to remove!\n");
    }

    while (rem_ptr != NULL) {
        if (rem_ptr->number == i) {
            if (prev == NULL) {
                free(tasks);
                change_number = 1;
            } else {
                prev->next = rem_ptr->next;
                free(rem_ptr);
                rem_ptr = prev->next;
                change_number = 1;
            }

        }
        if (change_number == 1) {
            rem_ptr->number = rem_ptr->number - 1;
        }
        prev = rem_ptr;
        rem_ptr = rem_ptr->next;
    }

    return tasks;
}


/********
 * Menu *
 ********/

task *menu(task *tasks, char *comm)
{
    if (strcmp(comm, "-a") == 0) {
        tasks = add_task(tasks);
    } else if (strcmp(comm, "-cm") == 0) {
        print_commands();
    } else if (strcmp(comm, "-l") == 0) {
        print_tasks(tasks);
    } else if (strcmp(comm, "-wr") == 0) {
        write_file(tasks);
    } else if (strcmp(comm, "-rd") == 0) {
        tasks = read_file(tasks);
    } else if (strcmp(comm, "-e") == 0) {
        tasks = empty_list(tasks);
    } else if (strcmp(comm, "-r") == 0) {
        tasks = remove_task(tasks);
    } else {
        printf("\n%s is NOT a valid command\n", comm);
    }

    return tasks;
}

