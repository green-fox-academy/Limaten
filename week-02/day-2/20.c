#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
	uint8_t z = 13;

	// if z is between 10 and 20 print 'Sweet!'
	// if less than 10 print 'More!',
	// if more than 20 print 'Less!'

    if(z < 20 && z > 10){
        printf("Sweet!");
	}
	else if(z < 10){
        printf("More!");
	}
	else if(z > 20){
        printf("Less!");
	}

	return 0;
}
