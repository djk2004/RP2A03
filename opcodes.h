#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t byte;
typedef bool bit;

struct State {
    byte *memory;
    unsigned short program_counter;
    byte s, p, a, x, y;
    unsigned long cycles;
    bit carry, zero, interrupt_disable, decimal, break_command, overflow, negative;
};

int run_opcode(byte opcode, struct State* state);

#endif
