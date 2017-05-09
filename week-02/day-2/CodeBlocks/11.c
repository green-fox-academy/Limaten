#include <stdio.h>
#include <stdlib.h>

int main(){
	int k = 1521;

	// tell if k is dividable by 3 or 5

	if((k % 3 == 0) || (k % 5 == 0)){
        printf("k is dividable by 3 or 5");
	}
	else{
        printf("k is NOT dividable by 3 or 5");
	}

	return 0;
}
