#include <stdio.h>
#include <stdlib.h>

int main()
{
    char my_name_array[] = "My Name";

    //TODO:
    // Print out the array character-by-character

    int length = sizeof(my_name_array) / sizeof(my_name_array[0]);
    for (int i = 0; i < length; i++) {
        printf("%c\n", my_name_array[i]);
    }

    return 0;
}
