#include <stdio.h>

struct rectangular_cuboid {
    double a;
    double b;
    double c;
};

// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface
double get_surface(struct rectangular_cuboid rc)
{
    return rc.a * rc.b * 2 + rc.a * rc.c *2 + rc.b * rc.c * 2;
}

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume
double get_volume(struct rectangular_cuboid rc)
{
    return rc.a * rc.b * rc.c;
}

int main()
{
    struct rectangular_cuboid rc = {10, 20, 30};
    printf("%f\n", get_surface(rc));
    printf("%f\n", get_volume(rc));
    return 0;
}
