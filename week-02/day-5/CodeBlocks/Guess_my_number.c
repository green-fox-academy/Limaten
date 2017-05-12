#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int lives = 5;
    int randomNumber = 1;
    int maxNumber;
    int playersNumber;
    printf("Please enter the range, from 1 to X:\n");
    scanf("%d", &maxNumber);
    randomNumber += rand() % maxNumber;
    printf("I've the number between 1 and %d. You have %d lives.\n", maxNumber, lives);

    while(1){
        if(lives == 1){
            printf("Last chance!\n");
        }
        scanf("%d", &playersNumber);
        if(playersNumber == randomNumber){
            printf("That's my number. Congratulations!\n");
            return 0;
        }else if(playersNumber > randomNumber){
            lives--;
            printf("Too high. You have %d lives\n", lives);
        }else{
            lives--;
            printf("Too low. You have %d lives\n", lives);
        }
        if(lives == 0){
            printf("\nYou lost.\nGAME OVER\n");
            printf("My number was %d.\n", randomNumber);
            return 0;
        }
    }
}
