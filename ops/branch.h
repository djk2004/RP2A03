#ifndef BRANCH_H
#define BRANCH_H

#include "../state.h"

int nop(struct State *state);

// branch on plus, when negative is clear
int bpl(struct State *state);

// branch on minus, when negative is set
int bmi(struct State *state);

// branch if overflow is clear
int bvc(struct State *state);

// branch if overflow is set
int bvs(struct State *state);

// branch if carry is clear
int bcc(struct State *state);

// branch if carry is set
int bcs(struct State *state);

// branch if not equal, when zero is clear
int bne(struct State *state);

// branch if equal, when zero is set
int beq(struct State *state);

#endif