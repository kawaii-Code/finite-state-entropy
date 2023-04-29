#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fse_internals.h"


#define SYMBOL_COUNT 256
#define NO_SYMBOL    -1

FrequencySymbol *counter_count_symbols_in_file(FILE *file, int *outSymbolCount, int *outInputLength) {
  int frequencies[SYMBOL_COUNT];
  memset(frequencies, NO_SYMBOL, sizeof *frequencies * SYMBOL_COUNT);

  char c;
  int inputLength = 0;
  while ((c = fgetc(file)) != EOF) {
    if (frequencies[c] == NO_SYMBOL)
      frequencies[c] = 1;
    else
      frequencies[c] += 1;
    inputLength++;
  }

  int countSymbols = 0;
  for (int i = 0; i < SYMBOL_COUNT; i++)
    if (frequencies[i] != NO_SYMBOL)
      countSymbols++;

  FrequencySymbol *result = malloc(sizeof(FrequencySymbol) * countSymbols);
  int symbolIndex = 0;
  for (int i = 0; i < SYMBOL_COUNT; i++)
    if (frequencies[i] != NO_SYMBOL)
      result[symbolIndex++] = (FrequencySymbol) { .frequency = frequencies[i], .symbol = (char)i };

  *outSymbolCount = countSymbols;
  *outInputLength = inputLength;
  return result;
}
