#if !defined(CLI_H)
#define CLI_H

typedef struct {
    char** commands;
    int* base;
} current_status;

typedef int (*handler)(current_status*);
typedef int (*arithmetic_function)(int, int);

typedef struct {
    char* function_name;
    handler function;
} function_map_element;

typedef struct {
    char* arithmetic_symbol;
    arithmetic_function ar_func;
} arithmetic_map_element;


void run_cli();
int split_into_commands(char* str, char* commands[]);
int handle_base(current_status*);
int handle_convert(current_status*);
int handle_op(current_status*);
int handle_exit(current_status*);
int handle_help(current_status*);
int is_valid_int(const char* str, int* val_out);

extern function_map_element function_mapping[]; // defined in CLI.c
extern arithmetic_map_element arithmetic_mapping[];



#endif // CLI_H
