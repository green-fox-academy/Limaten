#include <stdio.h>
#include <string.h>

struct Pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirates
double sumGold(struct Pirate * ptr, int length) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += ptr->gold_count;
        ptr++;
    }
    return sum;
}
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate

double avgGold(struct Pirate * ptr, int length) {
    return sumGold(ptr, length) / length;
}
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
// richest that has wooden leg
char* richest(struct Pirate * ptr, int length) {
    char* pName[256];
    int max = 0;

    for(int i = 0; i < length; i++) {
        if(ptr->has_wooden_leg == 1) {
            if(ptr->gold_count > max) {
                max = ptr->gold_count;
                strcpy(pName, ptr->name);
            }
        }
        ptr++;
    }
    return pName;
}


int main() {
    struct Pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };

    printf("\nSum of Gold of all pirates: %.0f\n", sumGold(pirates, 6));
    printf("Average Gold / pirate: %.2f\n", avgGold(pirates, 6));
    printf("Richest pirate with wooden leg: %s\n", richest(pirates, 6));

    return 0;
}
