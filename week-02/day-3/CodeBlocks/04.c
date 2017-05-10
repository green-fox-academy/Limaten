#include <stdio.h>
#include <stdlib.h>


/* Write a non void function which has a paramters (let's say for example x).
The funtion than returns the "xth" fibonaci number.
What the hack is a fibonacci number? Search it on wikipedia!
*/

int xthFibonacci(int x);

int main(){
    int a = 7;

    printf("%dth Fibonacci number = %d", a, xthFibonacci(a));

    return 0;
}

int xthFibonacci(int x){
    int e = 1;
    int f = 0;
    int v = 0;
    int i;

    for(i = 0; i < x; i++){
        f = v + e;
        e = v;
        v = f;
    }
    return f;
}
