#include <stdio.h>

struct RectangularCuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double GetSurface(struct RectangularCuboid rc){
    return (rc.a * rc.b  + rc.a * rc.c + rc.b * rc.c) * 2;
}
// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double GetVolume(struct RectangularCuboid rc) {
    return rc.a * rc.b * rc.a;
}


int main() {
    struct RectangularCuboid recub;
    printf("One side:\n");
    scanf("%lf", &recub.a);
    printf("Another side:\n");
    scanf("%lf", &recub.b);
    printf("Last side:\n");
    scanf("%lf", &recub.c);
    printf("\nSurface: %f\n", GetSurface(recub));
    printf("\nVolume: %f\n", GetVolume(recub));
    return 0;
}
