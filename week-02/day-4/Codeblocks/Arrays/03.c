#include <stdio.h>
#include <stdint.h>

int main() {
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};

	//TODO:
    // Print out the content of the arrays
    for(uint8_t i = 0; i < sizeof(int_array)/sizeof(int); i++){
        printf("%d\n", int_array[i]);
    }

    printf("\n");

    for(uint8_t i = 0; i < sizeof(float_array)/sizeof(float); i++){
        printf("%.2f\n", float_array[i]);
    }

    return 0;
}
