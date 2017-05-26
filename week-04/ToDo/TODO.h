
typedef struct task{
    char name[256];
    int number;
    int priority;
    struct task *next;
}task;

task *menu(task* tasks, char* comm);

void print_commands();

task *add_task(task *tasks);

void print_tasks(task *tasks);

void write_to_file(task *tasks);

task *read_file(task *tasks);

task *empty_list(task *tasks);
