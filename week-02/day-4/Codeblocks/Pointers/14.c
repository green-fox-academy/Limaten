#include <stdio.h>
#include <stdint.h>

void safeUnion(int *a, int l_a, int *b, int l_b, int *result, int l_res) {
    //TODO:
    for(uint8_t i = 0; i < l_a; i++){
        result[i] = a[i];
    }
    for(uint8_t i = 0; i < l_b; i++){
        result[l_a+i] = b[i];
    }

    return;
}

int main() {
    int a[3] = {1,2,3};
    int b[3] = {4,5,6};
    int c[6];
    safeUnion(a,3,b,3,c,6);
    for (int i = 0; i<6; i++) {
        printf("%d\n", c[i]);
    }
    return 0;
}
