#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>

typedef uint8_t byte;

struct State {
    byte *memory;
    unsigned short pc;
    byte s, p, a, x, y;
    byte cycle_counter;
};

int run_opcode(byte opcode, struct State* state);

#endif
