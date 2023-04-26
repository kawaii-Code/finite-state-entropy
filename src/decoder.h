#ifndef DECODER_H
#define DECODER_H

#include "encoder.h"

void decoder_create(int lastDecoderState, int initialLength, const char *stringToEncode);
char decoder_decode();

#endif
