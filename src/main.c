#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encoding_table.h"
#include "string_operations.h"
#include "encoder.h"
#include "decoder.h"

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

const char *encode(int n, FrequencySymbol *symbols, const char *stringToEncode) {
  int length = strlen(stringToEncode);

  char *result = string_new(length + 1);
  encoder_create(n, length, symbols);
  for (int i = 0; i < length; i++) {
    int encoded = encoder_encode(stringToEncode[i]);
    int padding = table_range_bit_size(stringToEncode[i], encoder_get_state());
    string_concat_binary(result, encoded, padding);
  }

  return result;
}

const char *decode(int n, int lastDecoderState, int initialLength, const char *stringToDecode) {
  char reversedEncodedString[strlen(stringToDecode) + 1];
  string_reverse(reversedEncodedString, stringToDecode);

  decoder_create(lastDecoderState, initialLength, reversedEncodedString);
  char accumulator[strlen(stringToDecode) + 1];
  accumulator[0] = '\0';
  for (int i = 0; i < initialLength; i++) {
    char decoded = decoder_decode();
    string_concat_char(accumulator, decoded);
  }
  char *result = string_new(initialLength);
  string_reverse(result, accumulator);

  return result;
}

// TEST 1
// abcaabaa -->
// 00-101-1-0-11-1-1

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
    perror("Provide an option -e or -d to specify, whether the program should encode or decode the input!");
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

  int length = 0;
  FrequencySymbol symbols[n];
  for (int i = 0; i < n; i++) {
    FrequencySymbol next = read_frequency_symbol();
    symbols[i] = next;
    length += next.frequency;
  }

  if ((length & (length - 1)) != 0) {
    normalize_input(n, symbols, length);
  }

  char input[100];
  scanf("%s100", input);

  table_create(n, symbols);
  if (isEncode) {
    printf("\nEncoding string '%s'...\n", input);
    const char *encodedString = encode(n, symbols, input);
    printf("Encoded: %s, last state: %d\n", encodedString, encoder_get_state());
  } else {
    int lastState = read_int();
    printf("\nDecoding string '%s'...\n", input);
    const char *decodedString = decode(n, lastState, length, input);
    printf("Decoded: %s\n", decodedString);
  }
}
