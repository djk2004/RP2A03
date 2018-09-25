#include "../state.h"
#include "../binary.h"

int cmp_zero_page(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    struct Result r = subtract(state->a, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}
