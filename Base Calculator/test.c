#include <stdio.h>
#include "converters.h"
#include <stdlib.h>

int main() {
    int val = 22;
    int base = 3;
    int curr;
    printf("Initial value: %d\n", val);
    int flag = int_to_base(val,&curr, base);
    if (flag == -1) {
        fprintf(stderr, "Error encountered when converting\n");
        exit(-1);
    }
    printf("Value after conversion: %d\n", curr);
    return 0;
}