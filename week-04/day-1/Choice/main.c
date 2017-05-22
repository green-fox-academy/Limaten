#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number;
    int key;

    printf("\t**********\n\tHello User\n\t**********\nYou have an integer named 'number'\n");
    printf("Please enter your 'number'\n");
    scanf("%d", &number);
    printf("- for it's memory address please press 1\n");
    printf("- for it's current value please press 2\n");
    printf("- to double it's value please press 3\n");
    printf("- to exit please press any other key\n");

    while (1) {
        scanf("%d", &key);
        switch (key) {
            case 1:
                printf("It's memory address: %p\n", &number);
                break;
            case 2:
                printf("It's current value: %d\n", number);
                break;
            case 3:
                number = number * 2;
                break;
            default:
                return 0;
        }
    }
    return 0;
}
