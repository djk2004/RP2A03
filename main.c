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
        .s = 0x01FF,  // starts at the top of stack memory and grows downward to 0x100
        .p = 0,
        .a = 0,
        .x = 0,
        .y = 0,
        .brk = 1
    };

    // program
    int index = 0;

    state.memory[0xFFFE] = 0x10;
    state.memory[0xFFFF] = 0x22;
    
    state.memory[index++] = 0xA0; // LDY $#88
    state.memory[index++] = 0x88;
    state.memory[index++] = 0x00;  // BRK

    index = 0x2210;
    state.memory[index++] = 0xA2; // LDX $#07
    state.memory[index++] = 0x07;
    state.memory[index++] = 0x02; // UNIMPLEMENTED

    state.program_counter = 0;
    int run_state = 0;
    instructions *current = (instructions*)malloc(sizeof(instructions*) * 9);
    while (run_state >= 0) {
        if (state.cycles % INTERRUPT_PERIOD_MS == 0) {
            // TODO: some interrupt tasks here, increment cycles as needed
            state.cycles++;
        } else {
            byte opcode = state.memory[state.program_counter];
            printf("%04X:  %02X\n", state.program_counter, opcode);
            increment_program_counter(&state);
            state.cycles++;
            int length = get_opcode_instructions(current, opcode);
            for (int i=0; i < length; i++) {
                run_state = (current[i])(&state);
                if (run_state == OK_IGNORE_CYCLE)
                    state.cycles++;
                else if (run_state == ERROR)
                    break;
            }
        }
    }
    free(current);

    // TODO: remove later
    printf("accumulator = %02X\n", state.a);
    printf("x = %02X\n", state.x);
    printf("y = %02X\n", state.y);
    printf("s = %04X\n", state.s);
    printf("negative = %d\n", state.negative);
    printf("overflow = %d\n", state.overflow);
    printf("break = %d\n", state.brk);
    printf("decimal = %d\n", state.decimal);
    printf("interrupt = %d\n", state.interrupt_disable);
    printf("zero = %d\n", state.zero);
    printf("carry = %d\n", state.carry);
    printf("program_counter = %04X\n", state.program_counter);
    printf("cycles = %lu\n", state.cycles);
    printf("_tmp_address = %04X\n", state._tmp_address);
    // printf("memory F0:F3 = %02X %02X %02X %02X\n", state.memory[0xF0], state.memory[0xF1], state.memory[0xF2], state.memory[0xF3]);
    printf("0x01FF = %02X\n", state.memory[0x01FF]);

    free(state.memory);
    return 0;
}
