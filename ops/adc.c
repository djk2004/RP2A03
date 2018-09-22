#include "../state.h"
#include "../binary.h"

int adc_a_tmp_address(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    struct Result r = add(state->a, value, state->carry);
    state->a = r.result;
    state->carry = r.carry;
    state->overflow = r.overflow;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}
