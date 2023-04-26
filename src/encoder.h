#ifndef ENCODER_H
#define ENCODER_H

void encoder_create(int n, int length, const FrequencySymbol *symbols);
int encoder_get_state();
int encoder_encode(char character);

#endif
