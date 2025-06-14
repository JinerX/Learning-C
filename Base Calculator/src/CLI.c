#include <stdio.h>
#include <stdlib.h>
#include "CLI.h"
#include <string.h>
#include "converters.h"
#include <errno.h>
#include <limits.h>
#include "arithmetic.h"
#include "constants.h"

function_map_element function_mapping[] = {
    {"base", handle_base},
    {"convert", handle_convert},
    {"op", handle_op},
    {"exit", handle_exit},
    {"help", handle_help}
};

arithmetic_map_element arithmetic_mapping[] = {
    {"*", times},
    {"+", add},
    {"-", subtract},
    {"/", divide}
};

int NUM_ARITHMETIC_OPERATIONS = sizeof(arithmetic_mapping)/sizeof(arithmetic_map_element);

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
        return -1;
    }

    errno = 0;
    // strtol converts string to long int, it takes char*, char pointer and base
    int val = strtol(str,&end_ptr,10);
    if (errno != 0 || val > INT_MAX || val < INT_MIN) {
        return -1;
    }
    if (*end_ptr != '\0') {
        // If not a valid number is passed strtol will not parse to the end 
        return -1;
    }

    *val_out = (int)val;
    return 0;
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
    current_status c_status = {NULL, &base};
    printf("Welcome to the simple base calculator! If you don't know the commands write help\n");
    int num_available_commands = sizeof(function_mapping) / sizeof(function_map_element);

    while(1) {
        char command[MAX_COMMAND_LENGTH];
        char *commands[MAX_ARGUMENTS];
        int command_executed_flag = 0;


        printf("Enter command: ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) != NULL) {
            command[strcspn(command, "\n")] = '\0';
        }
        

        // split command into tokens
        int num_args = split_into_commands(command, commands);
        c_status.commands = commands;
        char* init_command = commands[0];


        for (int i=0; i < num_available_commands; i++) {
            if (strcmp(function_mapping[i].function_name, init_command) == 0) {
                int flag = function_mapping[i].function(&c_status);
                command_executed_flag= 1;
            }
        }

        if (command_executed_flag == 0) {
            printf("Invalid command not doing anything\n");
        }
    }
    printf("Exiting CLI...\n");
}


int handle_base(current_status* c_status) {
    char* new_base = (*c_status).commands[1];
    int* old_base = (*c_status).base;
    
    int new_base_val;
    int flag = is_valid_int(new_base, &new_base_val);
    if (flag == -1) {
        fprintf(stderr, "Error base incorectly formatted, given base: %s\n", new_base);
        return -1;
    }
    if (2 > new_base_val || new_base_val > 36) {
        fprintf(stderr, "Base must be between 2 and 36\n");
        return -1;
    }
    *old_base = new_base_val;
    return 0;
}

int handle_exit(current_status* c_status) {
    exit(-1);
}

int handle_convert(current_status* c_status) {
    char* encoded_base = (*c_status).commands[1];
    char* encoded_val = (*c_status).commands[2];
    int i = 0;
    int* out_val = &i;
    int curr_base = (*(*c_status).base);
    char out_str[MAX_NUMBER_SIZE];


    int encoded_base_val;
    int flag = is_valid_int(encoded_base, &encoded_base_val);
    if (flag == -1) {
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
    flag = int_to_base_char(tmp, out_str, curr_base);
    if (flag == -1) {
        fprintf(stderr, "error when converting from int to base\n");
        return -1;
    }
    printf("Converting from base: %d, to currently stored base %d, value %s is %s\n", encoded_base_val, curr_base, encoded_val, out_str);
    
    return 0;
}

int handle_op(current_status* c_status) {
    char* char_a = (*c_status).commands[1];
    char* op = (*c_status).commands[2];
    char* char_b = (*c_status).commands[3];
    int base = (*(*c_status).base);
    
    int a;
    int b;
    int flag = int_from_base(char_a, &a, base);
    if (flag == -1) {
        fprintf(stderr, "first value of the operation is not correct");
        return -1;
    }
    flag = int_from_base(char_b, &b, base);
    if (flag == -1) {
        fprintf(stderr, "Second value of the operation is not formatted properly");
        return -1;
    }
    for (int i = 0; i < NUM_ARITHMETIC_OPERATIONS; i++) {
        if (strcmp(op, arithmetic_mapping[i].arithmetic_symbol) == 0) {
            int tmp = arithmetic_mapping[i].ar_func(a,b);
            // int out;
            char out_str[MAX_NUMBER_SIZE];
            int flag = int_to_base_char(tmp, out_str, base);
            if (flag == -1) {
                fprintf(stderr, "Something went wrong during result conversion");
                return -1;
            }
            printf("Result of operation: %s\n", out_str);
            return 0;
        }
    }
    fprintf(stderr, "Operation specified not supported");
    return -1;
}

int handle_help(current_status* c_status) {
    printf("The calculator constantly stores a specified base by default it's 10\n");
    printf("======== Available commands ========\n");
    printf("1. base n - changes currently stores base to n\n");
    printf("2. convert m a - converts value a written in base m to currently stored base\n");
    printf("3. op a <op> b - performs specified operation on values a and b in currently stored base\n");
    printf("3*. Supported operations include: +, -, *, \\ \n");
    printf("4. exit to exit the calculator\n");

}