#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
	int a = 654;
	uint64_t b = 654987312;

	// Tell if the reminder of b devided by a is 3
	if(b % a == 3){
        printf("the reminder of b devided by a is 3");
	}

	return 0;
}
