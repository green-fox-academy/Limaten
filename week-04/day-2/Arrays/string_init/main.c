#include <stdio.h>
#include <stdlib.h>

int main()
{
    char char_array[] = {'a', 'b', 'c', 'd'};
    char char_array_the_same[] = "abcd";

    //TODO:
    // Print out the two arrays character-by-character
    int length1 = sizeof(char_array) / sizeof(char_array[0]);
    for (int i = 0; i < length1; i++) {
        printf("%c\n", char_array[i]);
    }

    int length2 = sizeof(char_array_the_same) / sizeof(char_array_the_same[0]);
    for (int i = 0; i < length2; i++) {
        printf("%c\n", char_array_the_same[i]);
    }
    //TODO:
    // What is the difference between the arrays?
    printf("length1: %d\nlength2: %d\n", length1, length2);
    // char_array_the_same has an '\0' at the end

    return 0;
}
