#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Print out the addresses with and without pointer
print out the values with and without pointer
 */


int main()
{
    int number = 2017;
    float Pi = 3.14;
    char letter = 't';

    int *ptri = &number;
    float *ptrf = &Pi;
    char *ptrc = &letter;

    printf("%p\n", &number);
    printf("%p\n", ptri);
    printf("%p\n", &Pi);
    printf("%p\n", ptrf);
    printf("%p\n", &letter);
    printf("%p\n\n", ptrc);

    printf("%d\n", number);
    printf("%d\n", *ptri);
    printf("%f\n", Pi);
    printf("%f\n", *ptrf);
    printf("%c\n", letter);
    printf("%c\n\n", *ptrc);

    return 0;
}
