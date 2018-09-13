#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "opcodes.h"

const int INTERRUPT_PERIOD_MS = 60000;
const int MAX_MEMORY_BYTES = 65536;

int main() {
    struct State state = { 
        .memory = (byte*)calloc(MAX_MEMORY_BYTES, sizeof(byte)),
        .pc = 0,
        .s = 0,
        .p = 0,
        .a = 0,
        .x = 0,
        .y = 0,
        .cycle_counter = 0
    };


    // TODO: load something into memory here

    state.cycle_counter = INTERRUPT_PERIOD_MS;
    state.pc = 0;  // TODO: set initial memory location somehow

    bool is_running = true;
    while (is_running) {
        byte opcode = state.memory[state.pc++];  // TODO: make sure that program counter is incremented properly
        // cycle_counter -= cycles[opcode];  // TODO: define cycles

        run_opcode(opcode, &state);

        if (state.cycle_counter <= 0) {
            // TODO: some interrupt tasks here

            state.cycle_counter += INTERRUPT_PERIOD_MS;
            // TODO: find a way to set is_running to false here when needed
            // if (can_shutdown)
            //     is_running = false;
        }
    }

    free(state.memory);
    return 0;
}
