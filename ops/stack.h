#ifndef STACK_H
#define STACK_H

#include "../state.h"

// transfer between the x register and the stack pointer
int tsx(struct State *state);
int txs(struct State *state);

#endif