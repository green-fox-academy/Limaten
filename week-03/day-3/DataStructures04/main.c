#include <stdio.h>

enum CarType {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct Car {
    enum CarType type;
    double km;
    double gas;
};

// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

void carPrint(struct Car car) {
    if(car.type == 3) {
        printf("type: %d\n", car.type);
        printf("km: %f\n", car.km);
    } else {
        printf("type: %d\n", car.type);
        printf("km: %f\n", car.km);
        printf("gas: %f\n", car.gas);
    }
}


int main() {
    struct Car qwe = {VOLVO, 100000, 6.5};
    struct Car asd = {TESLA, 15000, 0};
    struct Car zxc = {TOYOTA, 68000, 3.2};

    carPrint(qwe);
    carPrint(asd);
    carPrint(zxc);

    return 0;
}
