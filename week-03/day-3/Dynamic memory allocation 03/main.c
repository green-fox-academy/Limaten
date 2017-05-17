#include <stdio.h>
#include <stdlib.h>

/** TODO:
 * Create a function called "range" that creates a new array and returns a pointer to it.
 * It should fill the array with numbers based on it's paramters.
 * It should take 3 paramters:
 * int from: the first number in the array
 * int to: it will fill the array till it would reach this number (so this number is not in the array)
 * int step: the step between the numbers
 *
 * Examples:
 * range(0, 10, 2) -> {0, 2, 4, 6, 8}
 * range(1, -8, -3) -> {1, -2, -5}
 *
 * It should delete any dynamically allocated resource before the program exits.
 */

int* range(int from, int to, int step) {
    int size = abs((to - from) / step);
    int* array = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++) {
        array[i] = from + i * step;
    }

    return array;
}


int main() {
    int f, t ,s;
    printf("From:\n");
    scanf("%d", &f);
    printf("To:\n");
    scanf("%d", &t);
    printf("Step:\n");
    scanf("%d", &s);

    int* ptr = range(f, t, s);

    for(int i = 0; i < abs((t - f) / s); i++) {
        printf("%d ", ptr[i]);
    }

    free(ptr);
    return 0;
}
