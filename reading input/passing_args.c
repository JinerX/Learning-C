/*
Program presents passing arguments to a program
*/

#include <stdio.h>
#include <errno.h> // for errno
#include <limits.h> // for INT_MAX, INT_MIN
#include <stdlib.h>


int is_valid_int(const char* str, int* val_out) {
    /*
        Function takes array of chars(string) as input and pointer to an int.
        It checks if given string is a valid int if so returns 1 and writes it to val_out
        else returns 0
    */
   char* end_ptr;

   
    // initial checks
    if (str == NULL || *str == '\0') {
        //return 0 if string is null or just end
        return 0;
    }

    errno = 0;
    // strtol converts string to long int, it takes char*, char pointer and base
    int val = strtol(str,&end_ptr,10);
    if (errno != 0 || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    if (*end_ptr != '\0') {
        // If not a valid number is passed strtol will not parse to the end 
        return 0;
    }

    *val_out = (int)val;
    return 1;
}



int main(int argc, char** argv) {
    // Example usage: ./filename <name> <age>
    if (argc != 3) {
        fprintf(stderr, "Usage: ./filename <name> <age>\n");
        exit(1);
    }
    char* name = argv[1];
    int age;
    int success_flag = is_valid_int(argv[2], &age);
    if (success_flag == 0) {
        fprintf(stderr, "Invalid age, must be a valid integer value\n");
        exit(1);
    }
    printf("Hi! Your name is: %s, and your age is %d\n", name, age);
    return 0;
}
