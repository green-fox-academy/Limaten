#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} point_t;

// TODO:
// Create a function the constructs a Point (returns a pointer to a new point)
// It should take it's x and y coordinate as parameter
point_t *point(point_t ex)
{
    point_t *tmp = malloc(sizeof(point_t));
    tmp->x = ex.x;
    tmp->y = ex.y;
    return tmp;
}

// TODO:
// Create a function that takes 2 Points as a pointer and returns the distance between them
double distance(point_t *ptr1, point_t *ptr2)
{
    int a = abs(ptr1->x - ptr2->x);
    int b = abs(ptr1->y - ptr2->y);
    return sqrt(a * a + b * b);
}


int main()
{
    point_t example1 = {3, 4};
    point_t example2 = {50, 60};
    point_t *pte1 = point(example1);
    point_t *pte2 = point(example2);

    printf("%f\n", distance(pte1, pte2));
    free(pte1);
    free(pte2);
    return 0;
}
