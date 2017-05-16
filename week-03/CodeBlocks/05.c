#include <stdio.h>

int main() {

    float result;
    int a = 5;
    int b = 4;

    // Look at this, run the code
    result = a / b;
    printf("%f\n", result);

    // What the hack?! 5/4 is 1.25, but the program prints out 1
    // This is because a and b has a type on int
    // The compiler in this case handles them as natural numbers,
    // so the a/b will give a natural number result.
    // We have to say to the compiler to handle those numbers as float.
    // TODO:
    // Cast "a" to float and see the result again
    result = (float)a / b;
    printf("%f\n", result);

    // TODO:
    // Cast "b" to float and see the results
    result = a / (float)b;
    printf("%f\n", result);

    // See? If you cast one of the variables to float than the problem will
    // not come up.

    return 0;
}
