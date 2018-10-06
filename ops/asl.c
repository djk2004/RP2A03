#include "../state.h"
#include "../binary.h"

int asl_memory(struct State *state) {
    struct Result r = shift_left_one(state->_tmp_byte);
    state->_tmp_byte = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int asl_accumulator(struct State *state) {
    struct Result r = shift_left_one(state->a);
    state->a = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}