#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

int to_int(char value);

char to_char(int value);

char *string_new(int length);

void to_string(char *dest, char value);

void string_reverse(char *dest, const char *string_to_reverse);

void string_concat_char(char *dest, char value);

void string_concat_binary(char *dest, int value, int padding);

#endif
