#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "opcodes.h"

const int INTERRUPT_PERIOD_MS = 60000;
const int MAX_MEMORY_BYTES = 65536;

int main() {
    struct State state = { 
        .memory = (byte*)calloc(MAX_MEMORY_BYTES, sizeof(byte)),
        .program_counter = 0,
        .cycles = 0,
        .s = 0,
        .p = 0,
        .a = 0,
        .x = 0,
        .y = 0
    };


    // TODO: load something into memory here
    state.a = 0x80;
    state.memory[0xCD] = 0x00; // zero page

    // program
    state.memory[0x00] = 0x65;
    state.memory[0x01] = 0xCD;

    state.program_counter = 0;
    int run_state = 0;
    while (run_state == 0) {
        if (state.cycles % INTERRUPT_PERIOD_MS == 0) {
            // TODO: some interrupt tasks here, increment cycles as needed
            state.cycles++;
        } else {
            byte opcode = state.memory[state.program_counter++];
            state.cycles++;
            instructions *current = get_opcode_instructions(opcode);
            for (int i=0; ((*current)[i]) != NULL; i++) {
                run_state = ((*current)[i])(&state);
                state.cycles++;
            }
        }
    }

    // TODO: remove later
    printf("accumulator = %02X\n", state.a);
    printf("negative = %d\n", state.negative);
    printf("zero = %d\n", state.zero);
    printf("overflow = %d\n", state.overflow);
    printf("carry = %d\n", state.carry);
    printf("program_counter = %02X\n", state.program_counter);
    printf("cycles = %lu\n", state.cycles);

    free(state.memory);
    return 0;
}
