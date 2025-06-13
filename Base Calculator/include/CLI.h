#if !defined(CLI_H)
#define CLI_H

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 5

void run_cli();
int split_into_commands(char* str, char* commands[]);
int handle_base(char* new_base, int* old_base);
int handle_convert(char* encoded_base, char* encoded_val, int curr_base, int* out_val);
int handle_op(char* val_1, char* val_2, char* op, int* out_val);
int is_valid_int(const char* str, int* val_out);


#endif // CLI_H
