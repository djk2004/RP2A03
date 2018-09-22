#include "../state.h"

int eor_a_tmp_address(struct State *state) {
    state->a ^= state->memory[state->_tmp_address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return 0;
}
