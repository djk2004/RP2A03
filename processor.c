#include <stdio.h>
#include "processor.h"

int opcode_0(struct State *state) {
    printf("opcode 0\n");
    return 0;
}

int opcode_1(struct State *state) {
    printf("opcode 1\n");
    return 0;
}

int opcode_2(struct State *state) {
    printf("opcode 2\n");
    return 0;
}

int (*opcodes[])(struct State*) = { 
    opcode_0,
    opcode_1,
    opcode_2
 };

int run_opcode(byte opcode, struct State* state) {
    return opcodes[opcode](state);
}
