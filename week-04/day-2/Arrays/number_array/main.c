#include <stdio.h>
#include <stdlib.h>

int main()
{
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};

    //TODO:
    // Print out the content of the arrays

    int length1 = sizeof(int_array) / sizeof(int_array[0]);
    for (int i = 0; i < length1; i++) {
        printf("%d\n", int_array[i]);
    }

    int length2 = sizeof(float_array) / sizeof(float_array[0]);
    for (int i = 0; i < length2; i++) {
        printf("%.3f\n", float_array[i]);
    }

    return 0;
}
