#ifndef STATE_H
#define STATE_H

#include "binary.h"

extern const int OK;
extern const int OK_IGNORE_CYCLE;
extern const int ERROR;

struct State {
    byte *memory;
    unsigned short program_counter, s;
    byte p, a, x, y;
    unsigned long cycles;
    bit carry, zero, interrupt_disable, decimal, brk, overflow, negative;

    // The following are used to store state between cycles
    unsigned short _tmp_address, _tmp_byte;
};

int increment_program_counter(struct State *state);

#endif
