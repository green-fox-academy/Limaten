#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int maxNumber;
    int minNumber = 1;
    int playersNumber;
    printf("Please enter the range, from 1 to X:\n");
    scanf("%d", &maxNumber);
    printf("I've the number between 1 and %d\n", maxNumber);
    maxNumber++;
    while(1){
        scanf("%d", &playersNumber);
        if(maxNumber - minNumber == 2){
            printf("That's my number. Congratulations!\n");
            return 0;
        }
        if((maxNumber - playersNumber == playersNumber-minNumber) || (maxNumber - playersNumber < playersNumber-minNumber)){
            printf("Too high\n");
            maxNumber = playersNumber;
        }else if(maxNumber - playersNumber > playersNumber-minNumber){
            printf("Too low\n");
            minNumber = playersNumber;
        }
    }
    return 0;
}
