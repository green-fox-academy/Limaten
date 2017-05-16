#include <stdio.h>
#include <stdlib.h>

// Define the TOTORO macro which holds a number
#define TOTORO

int main()
{
    // Use the #if, #elif, #else macros

    // If the TOTORO macro is greater than 3 print out "Greater than 3"
    #if TOTORO > 3
        printf("Greater than 3");

    // If the TOTORO macro is lower than 3 print out "Lower than 3"
	#elif TOTORO < 3
        printf("Lower than 3.");

	// Else print out "TOTORO is 3"
	#else
        printf("TOTORO is 3");
	#endif
    return 0;
}
