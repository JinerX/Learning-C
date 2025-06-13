/*
    Program shows how getchar works it reads one character from stdin and returns it as ASCII code
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int val = getchar();

    if (val == EOF) {
        fprintf(stderr, "Error when calling getchar\n");
        exit(-1);
    }

    printf("Got char: %c\n", val);
    return 0;
}
