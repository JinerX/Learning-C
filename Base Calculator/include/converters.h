#ifndef CONVERTERS_H
#define CONVERTERS_H

int int_from_base(char* str, int* out_val, int base);
int int_to_base(int val, int* out_val, int base);
int int_to_base_char(int val, char* out_val, int base);
void reverse(char* str);

#endif