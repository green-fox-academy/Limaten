#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a struct called CircularBuffer
// It should store:
// A pointer that points to the start of a dynamically allocated array of ints (could be null) (head pointer)
// A pointer that points to the end of the dynamically allocated array of ints (could be null) (tail pointer)
// A pointer that points to the currently readable buffer item (could be null) (read pointer))
// A pointer that points to the currently writable buffer item (could be null) (write pointer)
// The lenght of the buffer
typedef struct CircularBuffer {
    //int length;
    int *head;
    int *tail;
    int *read;
    int *write;
} CircularBuffer;

// TODO:
// Create a function that returns a dynamically allocated CircularBuffer (the buffer itself should be allocated as well, not just the array inside)
// It should take a normal array and it's length as argument, and it should fill all the buffer values from the array
CircularBuffer *new_circbuff(int *array, int length)
{
    int *buffer = malloc(length * sizeof(int));
    memcpy(buffer, array, length * sizeof(int));

    CircularBuffer *ptr  = malloc(sizeof(CircularBuffer));
    ptr->head = buffer;
    ptr->read = buffer;
    ptr->write = buffer;
    ptr->tail = &buffer[length-1];

    return ptr;
}
// TODO:
// Create a function that resizes a CircularBuffer, it should take a CircularBuffer as a pointer and change that buffers length and
// reallocate it's array as well. (copying it's values)
void resize(CircularBuffer *array, int new_lenght)
{
    int pos_read = (((int)(array->read)) - ((int)(array->head))) / sizeof(int) - 1;
    int pos_write = (((int)(array->write)) - ((int)(array->head))) / sizeof(int) - 1;

    array->head = realloc(array->head, new_lenght * sizeof(int));
    array->tail = &array->head[new_lenght - 1];
    array->read = &array->head[pos_read];
    array->write = &array->head[pos_write];
}
// TODO:
// Create a function that takes a CircularBuffer and returns a new CircularBuffer that only contains the even numbers from the old CircularBuffer
CircularBuffer *evens(CircularBuffer *array, int lenght)
{
    int cntr = 0;
    for (int i = 0; i < lenght; i++) {
        if (array->head[i] % 2 == 0)
            cntr ++;
    }

    int j = 0;
    int *even_array = malloc(cntr * sizeof(int));
    for (int i = 0; i < lenght; i++) {
        if (array->head[i] % 2 == 0) {
            even_array[j] = array->head[i];
            j++;
        }
    }

    CircularBuffer *ptr = new_circbuff(even_array, cntr);

    return ptr;
}
// TODO:
// Try all the functions in the main function, please deallocate any buffer and the array inside it after using them

int main()
{
    CircularBuffer* ptr;
    int array[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    ptr = new_circbuff(array, 12);

    printf("Length=12\n");
    for(int* i = ptr->head; i <= ptr->tail ; i++) {
        printf("@%p:", i);
        printf("%d\n", *i);
    }
    printf("\n\n\n");


    CircularBuffer *even_ptr = evens(ptr, 12);
    printf("Evens:\n");
    for(int* i = even_ptr->head; i <= even_ptr->tail ; i++) {
        printf("@%p:", i);
        printf("%d\n", *i);
    }
    printf("\n\n\n");


    resize(ptr, 24);
    printf("Length=24\n");
    for(int* i = ptr->head; i <= ptr->tail ; i++) {
        printf("@%p:", i);
        printf("%d\n", *i);
    }
    printf("\n\n\n");

    free(even_ptr);
    free(ptr->head);
    free(ptr);
    return 0;
}

