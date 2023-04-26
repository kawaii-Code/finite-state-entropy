#include <stdlib.h>
#include <stdio.h>

#include "encoding_table.h"

static int state;

void encoder_create(int n, int length, const FrequencySymbol *symbols) {
  state = 0;
}

int encoder_get_state() {
  return state;
}

int encoder_encode(char character) {
  int offset;
  FrequencySymbol *symbol = table_symbol_by_char(character);
  int rangeIndex = table_get_range_index(state, symbol, &offset);
  int nextState = table_state_by_char(character) + rangeIndex;
  
  state = nextState;
  return offset;
}
