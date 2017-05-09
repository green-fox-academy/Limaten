#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
	float w = 24.0;
	int out = 0;

	// if w is even increment out by one
	if((int)w % 2 == 0){
        out++;
	}

	printf("out = %d", out);

	return 0;
}
