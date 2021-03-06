#ifndef STATE_H
#define STATE_H

#include "binary.h"

extern const int OK;
extern const int OK_IGNORE_CYCLE;
extern const int OK_IGNORE_AND_BREAK;
extern const int ERROR;

struct State {
    byte *memory;
    unsigned short program_counter, s;
    byte p, a, x, y;
    bit carry, zero, interrupt_disable, decimal, brk, overflow, negative;

    // The following are used to store state between cycles
    unsigned short _tmp_address, _tmp_byte;
};

int increment_program_counter(struct State *state);
byte get_processor_status(struct State *state);

void increment_cycle(struct State *state);

#endif
