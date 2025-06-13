#include <stdio.h>
#include "converters.h"
#include "CLI.h"
#include <stdlib.h>

int main() {
    int base = 3;
    int val;
    char str[] = "2221";
    int flag = int_from_base(str, &val, base);
    if (flag == -1) {
        fprintf(stderr, "Error encountered in int_from_base\n");
        exit(-1);
    }
    printf("Integer value read: %d\n", val);
    run_cli();
    return 0;
}