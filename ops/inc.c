#include "../state.h"
#include "../binary.h"

int inc_memory(struct State *state) {
    struct Result r = add(state->_tmp_byte, 0x01, 0);
    state->_tmp_byte = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}