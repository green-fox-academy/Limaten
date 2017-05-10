#include <stdio.h>
#include <stdlib.h>

/* Write a non void function which returns the value of PI, so the following number:
3.14159
Try it out in the main function by printing out the result of the pi generator function!
*/
float PI();

int main(){
    printf("PI = %.5f", PI());
    return 0;
}

float PI(){
    return 3.14159;
}
