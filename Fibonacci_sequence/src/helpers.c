#include "helpers.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>


int is_valid_int(char* str, int* out_val) {
    // Initial checks
    if (str == NULL || *str == '\0') {
        fprintf(stderr, "String is not of valid format");
        return -1;
    }

    char* end_ptr;
    int val;
    errno = 0;
    val = strtol(str, &end_ptr, 10);
    if (*end_ptr != '\0') {
        fprintf(stderr, "Invalid value passed to convert");
        return -1;
    }
    if (INT_MIN  > val || INT_MAX < val) {
        fprintf(stderr, "Value not within int bounds");
        return -1;
    }
    if (errno != 0) {
        fprintf(stderr, "Errno ancountered an erro");
        return -1;
    }
    *out_val = (int)val;
    return 0;
}