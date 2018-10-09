#ifndef LOGIC_H
#define LOGIC_H

#include "../state.h"

// AND, OR, and XOR operations
int and_memory(struct State *state);
int ora_memory(struct State *state);
int eor_memory(struct State *state);
int and_immediate(struct State *state);
int ora_immediate(struct State *state);
int eor_immediate(struct State *state);

// Arithmetic shift left
int asl_memory(struct State *state);
int asl_accumulator(struct State *state);

// Logical shift right
int lsr_memory(struct State *state);
int lsr_accumulator(struct State *state);

// Rotate left
int rol_memory(struct State *state);
int rol_accumulator(struct State *state);

// Rotate right
int ror_memory(struct State *state);
int ror_accumulator(struct State *state);

#endif