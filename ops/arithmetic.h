#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "../state.h"

// Add with carry
int adc_memory(struct State *state);
int adc_immediate(struct State *state);

// Subtract with carry
int sbc_memory(struct State *state);
int sbc_immediate(struct State *state);

// Increment by 1
int inc(struct State *state);
int inx(struct State *state);
int iny(struct State *state);

// Decrement by 1
int dec(struct State *state);
int dex(struct State *state);
int dey(struct State *state);

#endif