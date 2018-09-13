#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef uint8_t byte;

struct State {
    byte *memory;
    unsigned short pc;
    byte s, p, a, x, y;
};

int run_opcode(byte opcode, struct State* state);

#endif
