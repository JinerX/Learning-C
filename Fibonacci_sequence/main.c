#include <stdio.h>
#include "helpers.h"
#include <time.h>
#include "fibonacci.h"
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./fibbonacci n\n");
        return -1;
    }

    int n;
    int flag = is_valid_int(argv[1], &n);
    if (flag == -1) {
        fprintf(stderr, "Incorrect formatting of the number\n");
        return -1;
    }

    time_t start_naive = clock();
    int val1 = naive_rec_fib(n);
    time_t end_naive = clock();
    double elapsed_naive = (double)(end_naive - start_naive) / CLOCKS_PER_SEC;

    time_t start_dp = clock();
    int* ptr = array_dp_fib(n);
    int val2 = ptr[n];
    time_t end_dp = clock();
    double elapsed_dp = (double)(end_dp - start_dp) / CLOCKS_PER_SEC;

    printf("val naive: %d, val dp: %d, time naive: %f, time dp: %f\n", val1, val2, elapsed_naive, elapsed_dp);
    free(ptr);

    // int a;
    // char* str = "12a3";
    // int flag = is_valid_int(str, &a);
    // if (flag == -1) {
    //     fprintf(stderr, "incorrect string\n`");
    //     return -1;
    // }
    // printf("COnverted string: %d\n", a);
    return 0;    
}