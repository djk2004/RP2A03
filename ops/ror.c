#include "../state.h"
#include "../binary.h"

int ror_memory(struct State *state) {
    struct Result r = shift_right_one(state->_tmp_byte);
    state->_tmp_byte = r.result | (r.carry << 7);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int ror_accumulator(struct State *state) {
    struct Result r = shift_right_one(state->a);
    state->a = r.result | (r.carry << 7);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}