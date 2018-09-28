#include "../state.h"

int eor(struct State *state, unsigned short address) {
    state->a ^= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return 0;
}

int eor_memory(struct State *state) {
    eor(state, state->_tmp_address);
    return 0;
}

int eor_immediate(struct State *state) {
    eor(state, state->program_counter++);
    return 0;
}