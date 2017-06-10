#include <stdio.h>
#include <stdlib.h>
#include "rs232.h"


int main()
{
    buffer_init();
    printf("\n Temperature logger\n");
    print_com();
    while (1)
        menu();
    return 0;
}
