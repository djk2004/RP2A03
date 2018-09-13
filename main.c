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
    state.a = 0xFA;
    state.memory[0xCD] = 0x03; // zero page

    // program
    state.memory[0x00] = 0x25;
    state.memory[0x01] = 0xCD;


    // state.cycle_counter = INTERRUPT_PERIOD_MS;
    state.program_counter = 0;  // TODO: set initial memory location somehow

    int run_state = 0;
    while (run_state == 0) {
        byte opcode = read_memory(&state, state.program_counter++);
        run_state = run_opcode(opcode, &state);

        // if (state.cycle_counter <= 0) {
        //     // TODO: some interrupt tasks here
        //     state.cycle_counter += INTERRUPT_PERIOD_MS;
        //     // TODO: find a way to set is_running to false here when needed
        //     // if (can_shutdown)
        //     //     is_running = false;
        // }
    }

    // TODO: remove later
    printf("accumulator = %02X\n", state.a);
    printf("negative = %d\n", state.negative);
    printf("zero = %d\n", state.zero);
    printf("program_counter = %02X\n", state.program_counter);
    printf("cycles = %lu\n", state.cycles);

    free(state.memory);
    return 0;
}
