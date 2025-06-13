#include "converters.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>


int int_from_base(char* str, int* out_val, int base) {
    /*
        Function converts a number passed as string in a given base to a decimal int
    */
    if (1 < base || base < 37) {
        fprintf(stderr, "Base must be between 2 and 36 inclusive\n");
        return -1;
    }
    // check validity of the string
    if (str == NULL || *str == '\0') {
        fprintf(stderr, "invalid string passed\n");
        return -1;
    }
    char* end_ptr;
    long val;
    errno = 0;
    val = strtol(str, &end_ptr, base);
    if (errno != 0 || val > INT_MAX || val < INT_MIN) {
        fprintf(stderr, "Invalid value within string\n");
        return -1;
    }
    if (*end_ptr != '\0') {
        fprintf(stderr, "Passed string is not a valid integer (non numerical values passed or wrong base)\n");
        return -1;
    }
    *out_val = (int)val;
    return 0;
}

int int_to_base(int val, int* out_val, int base) {
    /*
        Function converts given integer number to a form of specified base
    */
    if (out_val == NULL) {
        fprintf(stderr, "out pointer cannot be NULL\n");
        return -1;
    }
    if (base < 2 || base > 36) {
        fprintf(stderr, "base must be between 2 and 36 inclusive\n");
        return -1;
    }
    
    int curr = 0;
    int place = 1;
    while (val != 0) {
        int m = val % base;
        curr = curr + place * m;
        place = place * 10;
        val = val / base;
    }

    *out_val = curr;
    return 0;
}