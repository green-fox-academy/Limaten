#include <stdio.h>
#include <stdbool.h>
#define MARKET_PRICE 400
// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
struct house {
    int address;
    int price;
    int rooms;
    int area;
};
// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
bool worth_to_buy(struct house *h)
{
    if (h->price / h->area < MARKET_PRICE)
        return true;
    return false;
}
// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int good_houses(struct house *array, int length)
{
    int cntr = 0;
    for (int i = 0; i < length; i++) {
        if(worth_to_buy(array))
            cntr++;
        array++;
    }
    return cntr;
}

int main()
{
    struct house houses[] = {
        {15, 30000, 2, 60},
        {72, 25000, 2, 45},
        {159, 34000, 3, 86},
        {66, 11000, 1, 37}
    };

    printf("How many houses are worth to buy?\n");
    printf("%d", good_houses(houses, 4));

    return 0;
}
