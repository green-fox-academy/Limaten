#include <stdio.h>
#include <stdlib.h>

// TODO:
// Please create a program that asks for a count when it starts.
// It should ask for a number count times, then it shoud print the average of the numbers.
// It should delete any dynamically allocated resource before the program exits.

int main()
{
    int *ptr;
    int count;
    double sum = 0;
    printf("Give me an intiger number:\n");
    scanf("%d", &count);
    ptr = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        printf("Give me an other intiger number:\n");
        scanf("%d", &ptr[i]);
        sum += ptr[i];
    }

    printf("AVG: %f\n", sum / count);

    free(ptr);
    return 0;
}
