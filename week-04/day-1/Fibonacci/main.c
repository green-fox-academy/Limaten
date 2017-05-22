#include <stdio.h>
#include <stdlib.h>

int get_fibonacci_number(int nth) {
    if(nth > 0) {
        int fibonacci_number = 0;
        int next;
        int previous = 1;
        for (int i = 0; i < nth-1 ; ++i) {
            next = fibonacci_number + previous;
            previous = fibonacci_number;
            fibonacci_number = next;
        }
        return fibonacci_number;
    } else {
        return -1;
    }
}

int main()
{
    int number;

    printf("Please enter your number:\n");
    scanf("%d", &number);

    if (get_fibonacci_number(number) == -1) {
        printf("Not a valid number\n");
    } else {
        printf("%dth Fibonacci number: %d\n", number, get_fibonacci_number(number));
    }

    return 0;
}
