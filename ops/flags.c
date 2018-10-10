#include "../state.h"

int clc(struct State *state) {
    state->carry = 0;
    return OK;
}

int cld(struct State *state) {
    state->decimal = 0;
    return OK;
}

int clv(struct State *state) {
    state->overflow = 0;
    return OK;
}

int cli(struct State *state) {
    state->interrupt_disable = 0;
    return OK;
}

int sec(struct State *state) {
    state->carry = 1;
    return OK;
}

int sed(struct State *state) {
    state->decimal = 1;
    return OK;
}

int sei(struct State *state) {
    state->interrupt_disable = 1;
    return OK;
}

int bit_test_memory(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    state->zero = is_zero(state->a & value);
    state->negative = value & BIT_7;
    state->overflow = value & BIT_6;
    return OK;
}
