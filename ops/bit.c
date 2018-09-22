#include "../state.h"

int bit_test_zero_page(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    state->zero = is_zero(state->a & value);
    state->negative = value & BIT_7;
    state->overflow = value & BIT_6;
    return 0;
}
