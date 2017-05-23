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

int *range(int from, int to, int step)
{
    int *ptr;
    int size = abs((to - from) / step);
    ptr = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        ptr[i] = from + step * i;
    }
    return ptr;
}

int main()
{
    int *tmp = range(0, 10, 2);

    for (int i = 0; i < abs((10 - 0) / 2); i++) {
        printf("%d, ", tmp[i]);
    }

    free(tmp);
    return 0;
}
