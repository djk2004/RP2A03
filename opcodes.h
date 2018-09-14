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

    // The following are used to store state between cycles
    byte _tmp_address;
};

struct Opcode {
    byte opcode;

    // The first cycle of each opcode happens in the main loop, so this number must be one cycle less than
    // the total number of cycles needed to complete the operation.
    int cycles;
    
    // TODO: can this array be flexible?
    int (*instructions[8])(struct State*);
};

struct Opcode run_opcode(byte opcode, struct State* state);

#endif
