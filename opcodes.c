#include <stdio.h>
#include "opcodes.h"

int set_negative_bit(struct State *state, byte b) {
    state->negative = (b & 128) >> 7;
    return 0;
}

int set_zero_bit(struct State *state, byte b) {
    state->zero = b == 0;
    return 0;
}

int set_zero_page_address(struct State *state) {
    state->_tmp_address = state->memory[state->program_counter++];
    return 0;
}

int unimplemented(struct State *state) {
    printf("unimplemented opcode\n");
    return -1;
}

int and_zero_page(struct State *state) {
    state->a &= state->memory[state->_tmp_address];
    set_negative_bit(state, state->a);
    set_zero_bit(state, state->a);
    return 0;
}

int lda_zero_page(struct State *state) {
    state->a = state->memory[state->_tmp_address];
    set_negative_bit(state, state->a);
    set_zero_bit(state, state->a);
    return 0;
}

instructions unimplemented_opcode = {
    unimplemented,
    NULL
};

instructions and_zero_page_25 = {
    set_zero_page_address,
    and_zero_page,
    NULL
};

instructions lda_zero_page_A5 = {
    set_zero_page_address,
    lda_zero_page,
    NULL
};

instructions* get_opcode_instructions(byte opcode) {
    switch (opcode) {
        case 0x25: return &and_zero_page_25;
        case 0xA5: return &lda_zero_page_A5;
    }
    return &unimplemented_opcode;
}
