#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main() {
    int count;
    int sum = 0;
    printf("Please give me a number:\n");
    scanf("%d", &count);
    int* array = malloc(count * sizeof(int));
    printf("Please give me %d numbers\n", count);

    for(int i = 0; i < count; i++) {
        scanf("%d", &array[i]);
        sum += array[i];
    }

    printf("The average of the numbers is: %d\n", sum / count);

    free(array);

    return 0;
}
