#include <stdio.h>
#include <stdlib.h>

int main()
{
    int girls;
    int boys;

    printf("How many girls come to the party?\n");
    scanf("%d", &girls);
    printf("How many boys come to the party?\n");
    scanf("%d", &boys);

    if(girls == 0) {
        printf("Sasuge party\n");
    } else {
        if(girls + boys > 20) {
            if(girls == boys) {
                printf("The party is excellent!\n");
            } else {
                printf("Quite cool party!\n");
            }
        } else {
            printf("Average party...\n");
        }
    }
    return 0;
}
