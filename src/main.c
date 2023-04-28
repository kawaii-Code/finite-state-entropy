#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_operations.h"
#include "fse.h"

int read_int() {
  int result;
  scanf("%d", &result);
  return result;
}

FrequencySymbol read_frequency_symbol() {
  char symbol;
  int frequency;
  scanf("%*c%c:%d", &symbol, &frequency);
  return (FrequencySymbol) { symbol, frequency };
}

FrequencySymbol *read_frequency_symbols(int n, int *outLength) {
  int length = 0;
  FrequencySymbol *symbols = malloc(sizeof(FrequencySymbol) * n);
  for (int i = 0; i < n; i++) {
    FrequencySymbol next = read_frequency_symbol();
    symbols[i] = next;
    length += next.frequency;
  }

  *outLength = length;
  return symbols;
}

void normalize_input(int n, FrequencySymbol *symbols, int length) {
  int incrementIndex = 0;
  int tempLength = length;
  while ((tempLength & (tempLength - 1)) != 0) {
    symbols[incrementIndex].frequency++;
    tempLength++;
    incrementIndex = (incrementIndex + 1) % n;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Provide an option -e or -d to specify, whether the program should encode or decode the input!");
    return -1;
  } 

  int isEncode = 0;
  if (strcmp(argv[1], "-e") == 0) {
    isEncode = 1;
  } else if (strcmp(argv[1], "-d") == 0) {
    isEncode = 0;
  } else {
    printf("Unknown option '%s' provided! Available options: '-e', '-d'.", argv[1]);
    return -1;
  }

  int n = read_int();
  int length;
  FrequencySymbol *symbols = read_frequency_symbols(n, &length);

  if ((length & (length - 1)) != 0) {
    normalize_input(n, symbols, length);
  }

  char input[100];
  scanf("%s100", input);

  fse_init(n, length, symbols);
  if (isEncode) {
    printf("\nEncoding string '%s'...\n", input);
    int lastState;
    const char *encodedString = fse_encode(input, &lastState);
    printf("Encoded: %s, last state: %d\n", encodedString, lastState);
  } else {
    int lastState = read_int();
    printf("\nDecoding string '%s'...\n", input);
    const char *decodedString = fse_decode(input, lastState);
    printf("Decoded: %s\n", decodedString);
  }
}
