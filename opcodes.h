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

typedef int (*instructions[])(struct State*);
instructions* get_opcode_instructions(byte opcode);

#endif
