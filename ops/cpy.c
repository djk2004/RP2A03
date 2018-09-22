#include "../state.h"
#include "../binary.h"

int cpy_tmp_address(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    struct Result r = subtract(state->y, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}