#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number;
    printf("Hit mi with a number!\n");
    scanf("%d", &number);
    if(number % 2 == 0) {
        printf("Your number is even.\n");
    } else {
        printf("Your number is odd.");
    }

    return 0;
}
