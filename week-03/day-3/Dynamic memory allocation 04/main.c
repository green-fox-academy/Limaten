#include <stdio.h>
#include <stdlib.h>

// TODO:
/**
 * Create a function called "resize" that takes a pointer to an int array, it's size and it's new size,
 * then it should return a new pointer that points to the new resized array.
 * It should copy all the elements to the new array, if the array is bigger it should fill all the new slots with zeros.
 * It should delete the old array.
 */

int* resize(int* oldPtr, int oldSize, int newSize) {
    int* newPtr = calloc(newSize, sizeof(int));

    for(int i = 0; i < oldSize; i++) {
        newPtr[i] = oldPtr[i];
    }

    return newPtr;
}

int main() {
    int* oldArray = malloc(5 * sizeof(int));
    for(int i = 0; i < 5; i++) {
        oldArray[i] = i;
    }

    int* newArray = resize(oldArray, 5, 8);

    for(int i = 0; i < 8; i++) {
        printf("%d ", newArray[i]);
    }

    free(oldArray);
    free(newArray);
    return 0;
}
