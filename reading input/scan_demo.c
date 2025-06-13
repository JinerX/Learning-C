/*
scanf demo shows use of scanf

scanf(_Format, <pointers to assign values>)

scanf is pretty unsafe and hard to use properly, typically fgets is preferred
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int age;
    char* name;
    printf("Write your name and age: ");
    if (scanf("%s %d", name, &age) == EOF) {
        fprintf(stderr, "scanf encountered an erro\n");
        exit(-1);
    }
    printf("Name: %s, Age: %d\n", name, age);
}