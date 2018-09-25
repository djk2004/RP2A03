#include "../state.h"
#include "../binary.h"

int sbc_memory(struct State *state) {
    byte value = state->memory[state->_tmp_address];
    struct Result r = subtract(state->a, value, state->carry);
    state->a = r.result;
    state->carry = r.carry;
    state->overflow = r.overflow;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}
