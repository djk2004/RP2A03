#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "opcodes.h"

const int MAX_MEMORY_BYTES = 65536;

int main() {
    struct State state = { 
        .memory = (byte*)calloc(MAX_MEMORY_BYTES, sizeof(byte)),
        .program_counter = 0,
        .s = 0x01FF,  // starts at the top of stack memory and grows downward to 0x100
        .p = 0,
        .a = 0,
        .x = 0,
        .y = 0,
        .brk = 1
    };

    // program
    int index = 0;

    state.memory[0x00FF] = 0x01;

    state.memory[index++] = 0xA9; // LDA $#88
    state.memory[index++] = 0x88;
    state.memory[index++] = 0x65; // ADC $FF
    state.memory[index++] = 0xFF;
    state.memory[index++] = 0x30; // BMI $A1
    // state.memory[index++] = 0x10; // BPL $A1
    state.memory[index++] = 0xA1;
    state.memory[index++] = 0xAA; // TAX
    state.memory[index++] = 0x02; // UNIMPLEMENTED

    index += 0xA0;
    state.memory[index++] = 0xA8; // TAY
    state.memory[index++] = 0x02; // UNIMPLEMENTED

    state.program_counter = 0;
    int run_state = 0;
    instructions *current = (instructions*)malloc(sizeof(instructions*) * 9);
    while (run_state >= 0) {
        byte opcode = state.memory[state.program_counter];
        printf("%04X:  %02X\n", state.program_counter, opcode);
        increment_program_counter(&state);
        increment_cycle(&state);
        int length = get_opcode_instructions(current, opcode);
        for (int i=0; i < length; i++) {
            run_state = (current[i])(&state);
            if (run_state == OK) 
                increment_cycle(&state);
            else if (run_state == ERROR || run_state == OK_IGNORE_AND_BREAK)
                break;
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
    printf("_tmp_address = %04X\n", state._tmp_address);
    printf("_tmp_byte = %04X\n", state._tmp_byte);
    // printf("memory F0:F3 = %02X %02X %02X %02X\n", state.memory[0xF0], state.memory[0xF1], state.memory[0xF2], state.memory[0xF3]);
    // printf("0x01FF = %02X\n", state.memory[0x01FF]);

    free(state.memory);
    return 0;
}
