#ifndef OPCODES_H
#define OPCODES_H

#include "state.h"
#include "binary.h"

typedef int (*instructions)(struct State*);
void get_opcode_instructions(instructions *ops, byte opcode);

#endif
