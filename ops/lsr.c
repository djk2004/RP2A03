#include "../state.h"
#include "../binary.h"

int lsr_memory(struct State *state) {
    struct Result r = shift_right_one(state->_tmp_byte);
    state->_tmp_byte = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int lsr_accumulator(struct State *state) {
    struct Result r = shift_right_one(state->a);
    state->a = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}
