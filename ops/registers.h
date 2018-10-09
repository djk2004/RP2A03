#ifndef REGISTERS_H
#define REGISTERS_H

#include "../state.h"

// Transfer between registers
int txa(struct State *state);
int tya(struct State *state);
int tay(struct State *state);
int tax(struct State *state);

// Store register contents in memory
int sty_memory(struct State *state);
int stx_memory(struct State *state);
int sta_memory(struct State *state);

// Load memory contents into a register
int ldy_memory(struct State *state);
int ldx_memory(struct State *state);
int lda_memory(struct State *state);

// Load a value into a register
int ldy_immediate(struct State *state);
int ldx_immediate(struct State *state);
int lda_immediate(struct State *state);

// Compare memory contents with a register
int cmp_memory(struct State *state);
int cpx_memory(struct State *state);
int cpy_memory(struct State *state);

// Compare a value with a register
int cmp_immediate(struct State *state);
int cpx_immediate(struct State *state);
int cpy_immediate(struct State *state);

#endif