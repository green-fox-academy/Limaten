#include <stdio.h>
#include <stdint.h>

int main() {
     char buffer[255];   // Buffer variable for user input

     printf("What is Your name?\n");
    //TODO:
    // Get the user's name with gets
    gets(buffer);

    //TODO:
    // Print it out with puts
    puts(buffer);

    //TODO:
    // Get the user's pet name with getch
    getch();

    //TODO:
    // Print it out
    printf("Your name is :%s", buffer);

    return 0;
}
