#include <stdio.h>
#include <stdlib.h>

int main(){
	int i = 53625;

	// tell if it has 11 as a divisor

	if(i % 11 == 0){
        printf("i has 11 as a divisor");
	}
	else{
        printf("i does NOT have 11 as a divisor");
	}

	return 0;
}
