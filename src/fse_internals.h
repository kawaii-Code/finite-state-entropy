#ifndef FSE_INTERNALS_H
#define FSE_INTERNALS_H

typedef struct {
  char symbol;
  int frequency;
} FrequencySymbol;

void table_create(int n, FrequencySymbol *symbols);
int table_get_range_index(int currentState, FrequencySymbol *symbol, int *offsetOut);
int table_position_by_range(int currentState, FrequencySymbol *symbol);
int table_range_bit_size(char c, int state);
FrequencySymbol *table_symbol_by_char(char c);
FrequencySymbol *table_char_by_state(int state);
int table_state_by_char(char c);
int table_get_length();

void encoder_create(int n, int length, const FrequencySymbol *symbols);
int encoder_encode(char character);
int encoder_get_state();

void decoder_create(int lastDecoderState, int initialLength, const char *stringToEncode);
char decoder_decode();

#endif
