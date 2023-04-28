#include <string.h>

#include "fse_internals.h"
#include "string_operations.h"

static int _symbolCount;
static int _inputLength;
static FrequencySymbol *_symbols;

void fse_init(int n, int inputLength, FrequencySymbol *symbols) {
  _symbolCount = n;
  _inputLength = inputLength;
  _symbols = symbols;
  table_create(n, symbols);
}

const char *fse_encode(const char *string, int *outLastState) {
  encoder_create(_symbolCount, _inputLength, _symbols);

  char *result = string_new(_inputLength + 1);
  for (int i = 0; i < _inputLength; i++) {
    int encoded = encoder_encode(string[i]);
    int padding = table_range_bit_size(string[i], encoder_get_state());
    string_concat_binary(result, encoded, padding);
  }

  *outLastState = encoder_get_state();

  return result;
}

const char *fse_decode(const char *string, int encoderLastState) {
  char reversedEncodedString[strlen(string) + 1];
  string_reverse(reversedEncodedString, string);

  decoder_create(encoderLastState, _inputLength, reversedEncodedString);

  char accumulator[strlen(string) + 1];
  accumulator[0] = '\0';
  for (int i = 0; i < _inputLength; i++) {
    char decoded = decoder_decode();
    string_concat_char(accumulator, decoded);
  }

  char *result = string_new(_inputLength);
  string_reverse(result, accumulator);

  return result;
}
