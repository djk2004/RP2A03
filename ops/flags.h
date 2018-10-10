#ifndef FLAGS_H
#define FLAGS_H

#include "../state.h"

// Clear carry bit
int clc(struct State *state);

// Clear decimal bit
int cld(struct State *state);

// Clear overflow bit
int clv(struct State *state);

// Clear interrupt disable
int cli(struct State *state);

// Set the carry bit
int sec(struct State *state);

// Set the decimal bit
int sed(struct State *state);

// Set interrupt disable
int sei(struct State *state);

// Performs an AND with the accumulator and memory value, and sets the overflow and negative bits on the result
int bit_test_memory(struct State *state);

#endif