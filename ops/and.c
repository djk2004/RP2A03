#include "../state.h"

int and(struct State *state, unsigned short address) {
    state->a &= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return 0;
}

int and_memory(struct State *state) {
    and(state, state->_tmp_address);
    return 0;
}

int and_immediate(struct State *state) {
    and(state, state->program_counter++);
    return 0;
}
