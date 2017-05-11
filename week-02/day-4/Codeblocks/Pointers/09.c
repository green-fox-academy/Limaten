#include <stdio.h>
#include <stdint.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer;

    //TODO:
    // The "number_pointer" should point to the first element of the array called "numbers",
    // than please print its value with it.
    number_pointer = numbers;
    printf("%d", *number_pointer);


    return 0;
}
