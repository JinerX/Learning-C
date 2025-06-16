#include "fibonacci.h"
#include <stdio.h>
#include <stdlib.h>

int naive_rec_fib(int n) {
    if (n < 0) {
        fprintf(stderr, "n must be larger then or equal to 0\n");
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    else {
        return naive_rec_fib(n-1) + naive_rec_fib(n-2);
    }
}


int* array_dp_fib(int n) {
    if (n < 0) {
        fprintf(stderr, "n must be larger then or equal to 0\n");
        return NULL;
    }
    
    int* fibbNums = calloc(n+1, sizeof(int));
    fibbNums[0] = 0;
    fibbNums[1] = 1;

    for (int i=2; i < n+1; i++) {
        fibbNums[i] = fibbNums[i-1] + fibbNums[i-2];
    }
    return fibbNums;
}