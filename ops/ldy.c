#include "../state.h"

int ldy(struct State *state, unsigned short address) {
    state->y = state->memory[address];
    state->negative = is_negative(state->y);
    state->zero = is_zero(state->y);
    return 0;
}

int ldy_zero_page(struct State *state) {
    ldy(state, state->_tmp_address);
    return 0;
}

int ldy_immediate(struct State *state) {
    ldy(state, state->program_counter++);
    return 0;
}
