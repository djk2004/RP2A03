#include "../state.h"
#include "../binary.h"

int rol_memory(struct State *state) {
    struct Result r = shift_left_one(state->_tmp_byte);
    state->_tmp_byte = r.result | r.carry;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int rol_accumulator(struct State *state) {
    struct Result r = shift_left_one(state->a);
    state->a = r.result | r.carry;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}