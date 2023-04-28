#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fse_internals.h"

static FrequencySymbol *upperRow;
static int stateByChar[256];
static int length;

void fill_table(int n, FrequencySymbol *symbols) {
  int state = 0;
  for (int i = 0; i < n; i++) {
    stateByChar[symbols[i].symbol] = state;
    for (int j = 0; j < symbols[i].frequency; j++) {
      upperRow[state] = symbols[i];
      state++;
    }
  }
}

void table_create(int n, FrequencySymbol *symbols) {
  length = 0;
  for (int i = 0; i < n; i++)
    length += symbols[i].frequency; 

  upperRow = malloc(sizeof *upperRow * length);

  fill_table(n, symbols);
}

int table_get_range_index(int currentState, FrequencySymbol *symbol, int *offsetOut) {
  int result = 0;
  int frequency = symbol->frequency;
  int position = 0;
  int tempLength = length;

  while (frequency > 0) {
    int rangeLength = tempLength / frequency;
    if (position + rangeLength > currentState) {
      break;
    }
    position += rangeLength;
    tempLength -= rangeLength;
    frequency--;
    result++;
  }
  *offsetOut = currentState - position;
  
  return result;
}

int table_position_by_range(int currentState, FrequencySymbol *symbol) {
  int result = 0;
  int rangeIndex = 0;
  int frequency = symbol->frequency;
  int tempLength = length;

  while (rangeIndex != currentState - stateByChar[symbol->symbol]) {
    int range_length = tempLength / frequency;
    tempLength -= range_length;
    frequency--;
    result += range_length;
    rangeIndex++;
  }

  return result;
}

FrequencySymbol *table_symbol_by_char(char c) {
  for (int i = 0; i < length; i++)
    if (upperRow[i].symbol == c)
      return &upperRow[i];

  printf("No symbol '%c' found!", c);
  exit(10);
}

int table_range_bit_size(char c, int state) {
  FrequencySymbol *symbol = table_symbol_by_char(c);

  int frequency = symbol->frequency;
  int rangeIndex = 0;
  int tempLength = length;
  int rangeLength = 0;

  while (rangeIndex != state - stateByChar[symbol->symbol]) {
    rangeLength = tempLength / frequency;
    tempLength -= rangeLength;
    frequency--;
    rangeIndex++;
  }
  rangeLength = tempLength / frequency;

  return (int)log2(rangeLength);
}

FrequencySymbol *table_char_by_state(int state) {
  return &upperRow[state];
}

int table_state_by_char(char c) {
  return stateByChar[c];
}

int table_get_length() {
  return length;
}
