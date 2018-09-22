#ifndef OPCODES_H
#define OPCODES_H

#include "state.h"
#include "binary.h"

typedef int (*instructions[])(struct State*);
instructions* get_opcode_instructions(byte opcode);

#endif
