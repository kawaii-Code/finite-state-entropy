#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "string_operations.h"
#include "fse_internals.h"

static const char *input;
static int inputLength;
static int inputPosition;
static int state;

void decoder_create(int lastEncoderState, int initialLength, const char *stringToEncode) {
  inputLength = initialLength;
  inputPosition = 0;
  state = lastEncoderState;
  input = stringToEncode;
}

int read_bits(int count) {
  int mask = 1;
  int result = 0;
  for (int i = 0; i < count; i++) {
    char next = input[inputPosition++];
    int bit = to_int(next);
    result += bit ? mask : 0;
    mask <<= 1;
  }

  return result;
}

char decoder_decode() {
  char result = table_char_by_state(state)->symbol;
  FrequencySymbol *symbol = table_symbol_by_char(result);
  int rangeBitSize = table_range_bit_size(result, state);
  int offset = read_bits(rangeBitSize);
  int positionInRange = table_position_by_range(state, symbol);
  int nextState = positionInRange + offset;
  state = nextState;

  return result;
}
