#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the avarage of the elements.

double average(double *array, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++) {
        sum += array[i];
    }

    return sum / length;
}

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how much elements are under the avarage, and returns with that.

int under_average(double *array, int length)
{
    int tmp = 0;
    int avg = average(array, length);
    for (int i = 0; i < length; i++) {
        if(array[i] < avg)
            tmp++;
    }

    return tmp;
}

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.

double *new_array(double *array, int length)
{
    int size = under_average(array, length);
    int avg = average(array, length);
    int j = 0;
    double *tmp = malloc(size * sizeof(double));
    for (int i = 0; i < length; i++) {
        if(array[i] < avg) {
            tmp[j] = array[i];
            j++;
        }

    }
    return tmp;
}

int main()
{

    return 0;
}
