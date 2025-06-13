#include <stdio.h>
#include <stdlib.h>
#include "CLI.h"
#include <string.h>
#include "converters.h"

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



int split_into_commands(char* str, char* commands[]) {
    if (str == NULL || commands == NULL) {
        fprintf(stderr, "Neither command string nor commands array can be NULL");
        return -1;
    }
    char *token;
    int counter = 1;
    token = strtok(str, " \t");
    commands[0] = token;
    while (token != NULL) {
        token = strtok(NULL, " \t");
        commands[counter] = token;
        counter = counter + 1;
    }
    return counter;
}


void run_cli() {
    int base = 10;
    printf("Welcome to the simple base calculator! If you don't know the commands write help\n");
    
    while(1) {
        char command[MAX_COMMAND_LENGTH];
        char *commands[MAX_ARGUMENTS];
        printf("Enter command: ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
            command[strcspn(command, "\n")] = '\0';
        }

        // split command into tokens
        int num_args = split_into_commands(command, commands);
        char* init_command = commands[0];
        if (strcmp(init_command, "base")) {

        }
        else if () {
            /* code */
        }
        
    }
}


int handle_base(char* new_base, int* old_base) {
    int new_base_val;
    int flag = is_valid_int(new_base, &new_base_val);
    if (flag != -1) {
        fprintf(stderr, "Error base incorectly formatted\n");
        return -1;
    }
    if (2 > new_base_val || new_base_val > 36) {
        fprintf(stderr, "Base must be between 2 and 36\n");
        return -1;
    }
    *old_base = new_base_val;
    return 0;
}

int handle_convert(char* encoded_base, char* encoded_val, int curr_base, int* out_val) {
    int encoded_base_val;
    int flag = is_valid_int(encoded_base, &encoded_base_val);
    if (flag != -1) {
        fprintf(stderr, "Error base incorectly formatted\n");
        return -1;
    }
    if (2 > encoded_base_val || encoded_base_val > 36) {
        fprintf(stderr, "Base must be between 2 and 36\n");
        return -1;
    }
    int tmp;
    flag = int_from_base(encoded_val, &tmp, encoded_base_val);
    if (flag == -1) {
        fprintf(stderr, "error when converting from string to int\n");
        return -1;
    }
    flag = int_to_base(tmp, out_val, curr_base);
    if (flag == -1) {
        fprintf(stderr, "error when converting from int to base\n");
        return -1;
    }
    return 0;
}
int handle_op(char* val_1, char* val_2, char* op, int* out_val) {
    
}