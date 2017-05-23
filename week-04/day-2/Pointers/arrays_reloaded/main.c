#include <stdio.h>

int main()
{
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer = &numbers[0];
    //TODO:
    // The "number_pointer" should point to the third element of the array called "numbers",
    // than please print its value with it. Solve the problem without reusiong the "&" operator
    // for geting the address of the third element.
    number_pointer = &numbers[2];
    printf("%d\n", *number_pointer);

    number_pointer = numbers;
    number_pointer++;
    number_pointer++;
    printf("%d\n", *number_pointer);

    return 0;
}
