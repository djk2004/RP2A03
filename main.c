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

    // program
    int index = 0;

    // subtraction test, causes overflow and carry  -2 - (-128) = 126
    // state.memory[index++] = 0xA9;  // LDA #$FE
    // state.memory[index++] = 0xFE;
    // state.memory[index++] = 0xA2;  // LDX #$80
    // state.memory[index++] = 0x80;
    // state.memory[index++] = 0x86;  // STX $F0
    // state.memory[index++] = 0xF0;
    // state.memory[index++] = 0xE5;  // SBC $F0
    // state.memory[index++] = 0xF0;

    // causes an overflow and a carry  -2 + -128 = -130
    // state.memory[index++] = 0xA9;  // LDA #$80
    // state.memory[index++] = 0x80;
    // state.memory[index++] = 0xA2;  // LDX #$FE
    // state.memory[index++] = 0xFE;
    // state.memory[index++] = 0x86;  // STX $F0
    // state.memory[index++] = 0xF0;
    // state.memory[index++] = 0x65;  // ADC $F0
    // state.memory[index++] = 0xF0;

    state.memory[0x0021] = 0x55;
    state.memory[0x0055] = 0xAA;
    state.memory[index++] = 0xA2;  // LDX #$01
    state.memory[index++] = 0x01;
    state.memory[index++] = 0x01;  // ORA X, #$20
    state.memory[index++] = 0x20;

    state.program_counter = 0;
    int run_state = 0;
    while (run_state >= 0) {
        if (state.cycles % INTERRUPT_PERIOD_MS == 0) {
            // TODO: some interrupt tasks here, increment cycles as needed
            state.cycles++;
        } else {
            byte opcode = state.memory[state.program_counter++];
            state.cycles++;
            instructions *current = get_opcode_instructions(opcode);
            for (int i=0; ((*current)[i]) != NULL; i++) {
                run_state = ((*current)[i])(&state);
                if (run_state == OK_IGNORE_CYCLE)
                    state.cycles++;
            }
        }
    }

    // TODO: remove later
    printf("accumulator = %02X\n", state.a);
    printf("x = %02X\n", state.x);
    printf("y = %02X\n", state.y);
    printf("negative = %d\n", state.negative);
    printf("zero = %d\n", state.zero);
    printf("overflow = %d\n", state.overflow);
    printf("carry = %d\n", state.carry);
    printf("program_counter = %02X\n", state.program_counter);
    printf("cycles = %lu\n", state.cycles);
    printf("_tmp_address = %04X\n", state._tmp_address);
    // printf("memory F0:F3 = %02X %02X %02X %02X\n", state.memory[0xF0], state.memory[0xF1], state.memory[0xF2], state.memory[0xF3]);

    free(state.memory);
    return 0;
}
