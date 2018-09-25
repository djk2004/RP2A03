#include "../state.h"

int ldx(struct State *state, unsigned short address) {
    state->x = state->memory[address];
    state->negative = is_negative(state->x);
    state->zero = is_zero(state->x);
    return 0;
}

int ldx_zero_page(struct State *state) {
    ldx(state, state->_tmp_address);
    return 0;
}

int ldx_immediate(struct State *state) {
    ldx(state, state->program_counter++);
    return 0;
}
