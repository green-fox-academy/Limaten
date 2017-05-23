#include <stdio.h>
#define MARKET_PRICE 400

// TODO:
// Create a struct that represents a House
// It should store:
//  - The address of the house
//  - The price in EUR
//  - The number of rooms
//  - The area of the house in square meters
typedef struct {
    int address;
    int price;
    int rooms;
    double area;
} house;
// TODO:
// The market price of the houses is 400 EUR / square meters
// Create a function that takes a pointer to a house and decides if it's worth to buy
// (if the price is lower than the calculated price from it's area)
bool worth_to_buy(house *h)
{
    if (h->price < MARKET_PRICE)
        return true;
    return false;
}
// TODO:
// Create a function that takes an array of houses (and it's length), and counts the
// houses that are worth to buy.
int good_houses(house *array, int length)
{
    int cntr;

    for (int i = 0; i < length; i++) {
        if(worth_to_buy(*array[i]))
            cntr++;
    }
}




int main()
{

    return 0;
}
