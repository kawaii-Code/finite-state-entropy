#ifndef FSE_ENCODER_H
#define FSE_ENCODER_H

typedef struct {
  char symbol;
  int frequency;
} FrequencySymbol;

void fse_init(int n, int inputLength, FrequencySymbol *symbols);
const char *fse_encode(const char *string, int* outLastState);
const char *fse_decode(const char *string, int encoderLastState);
FrequencySymbol *counter_count_symbols_in_file(FILE *file, int *outSymbolCount, int *outInputLength);

#endif
