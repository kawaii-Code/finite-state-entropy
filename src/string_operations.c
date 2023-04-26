#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int to_int(char value) {
  return value - '0';
}

char to_char(int digit) {
  return digit + '0';
}

char *string_new(int length) {
  char *string = malloc(sizeof (char) * (length + 1));
  string[0] = '\0';
  return string;
}

void to_string(char *dest, char value) {
  dest[0] = value;
  dest[1] = '\0';
}

void string_reverse(char *dest, const char *input) {
  int length = strlen(input);
  for (int i = 0; i < length; i++) {
    dest[i] = input[length - i - 1];
  }
  dest[length] = '\0';
}

void string_concat_char(char *dest, char value) {
  int length = strlen(dest);
  dest[length] = value;
  dest[length + 1] = '\0';
}

void string_concat_binary(char *dest, int value, int padding) {
  for (int i = 0; i < padding; i++) {
    string_concat_char(dest, '0');
  }

  int appendIndex = strlen(dest) - 1;
  while (value > 0) {
    dest[appendIndex--] = to_char(value % 2);
    value /= 2;
  }
}
