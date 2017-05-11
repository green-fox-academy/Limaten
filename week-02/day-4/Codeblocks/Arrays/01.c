#include <stdio.h>
#include <stdint.h>

int main() {
    char my_name_array[] = "My Name";

	//TODO:
    // Print out the array character-by-character
    for(uint8_t i = 0; i < sizeof(my_name_array); i++){
        printf("%c\n", my_name_array[i]);
    }

    return 0;
}
