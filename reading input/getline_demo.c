/*
    Program shows how to use getline to read 1 line from input
    getline(buffer, size_of_buffer, stream) return -1 if error or EOF number of read chars otherwise
    we must call free on buffer because getline allocates it inside
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    char* line = NULL; // if buffer NULL then getline allocates it itself
    size_t len = 0;

    printf("Enter a line of text: ");
    size_t number_of_read = getline(&line, &len, stdin);
    
    if (number_of_read == -1) {
        fprintf(stderr, "Error when reading from getline");
        free(line);
        exit(-1);
    }

    printf("line read:\n%s", line);
    free(line);
    return 0;
}