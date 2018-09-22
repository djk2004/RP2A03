#ifndef STATE_H
#define STATE_H

#include "binary.h"

struct State {
    byte *memory;
    unsigned short program_counter;
    byte s, p, a, x, y;
    unsigned long cycles;
    bit carry, zero, interrupt_disable, decimal, break_command, overflow, negative;

    // The following are used to store state between cycles
    unsigned short _tmp_address;
};

#endif