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