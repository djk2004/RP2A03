#include "../state.h"

int ora(struct State *state, unsigned short address) {
    state->a |= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return 0;
}

int ora_memory(struct State *state) {
    ora(state, state->_tmp_address);
    return 0;
}

int ora_immediate(struct State *state) {
    ora(state, state->program_counter++);
    return 0;
}