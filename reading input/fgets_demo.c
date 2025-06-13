/*
using fgets - get a string from a stream

fgets(buffer, size, stream) - reads up to size characters into the buffer

*/

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_DESCRPIPTION 100


int main() {
    char name[MAX_NAME_LENGTH];
    char desc[MAX_DESCRPIPTION];
    printf("Enter your name: ");
    if (fgets(name, MAX_NAME_LENGTH, stdin) != NULL) {
        // fgets returns pointer to buffer if success NULL if fail
        name[strcspn(name, "\n")] = '\0';
        // if trailing newline turn it into \0
    }
    printf("\n");
    printf("Enter description: ");
    if (fgets(desc,MAX_DESCRPIPTION,stdin) != NULL) {
        desc[strcspn(desc, "\n")] = '\0';
    }
    printf("Name: %s, Description: %s\n", name, desc);
}