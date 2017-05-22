#include <stdio.h>
#include <stdlib.h>

int main()
{
    for(int i = 0; i < 100; i++) {
        printf("I wont't cheat on the test!\n");
    }

    int whileCounter = 0;
    while(whileCounter < 100) {
        printf("I wont't cheat on the test!\n");
        whileCounter++;
    }

    int doWhileCounter = 0;
    do {
        printf("I wont't cheat on the test!\n");
        doWhileCounter++;
    } while (doWhileCounter < 100);

    return 0;
}
