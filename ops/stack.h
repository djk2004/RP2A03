#ifndef STACK_H
#define STACK_H

#include "../state.h"

// transfer between the x register and the stack pointer
int tsx(struct State *state);
int txs(struct State *state);

// pushes the processor status onto the stack
int php(struct State *state);

// pushes the accumulator onto the stack
int pha(struct State *state);

// pulls the accumulator value from the stack
int pla(struct State *state);

// pulls the processor status from the stack
int plp(struct State *state);

#endif