#include <stdio.h>

int main()
{
    int high_number = 2;
    int low_number = 6655;

    int* hight_number_pointer = &high_number;
    int* low_number_pointer = &low_number;
    //TODO:
    // Please fix the problem and swap the value of the variables,
    // without using the "high_number" and the "low_number" variables.

    int tmp = *hight_number_pointer;
    *hight_number_pointer = *low_number_pointer;
    *low_number_pointer = tmp;

    printf("%d\n", *hight_number_pointer);
    printf("%d\n", *low_number_pointer);

    return 0;
}
