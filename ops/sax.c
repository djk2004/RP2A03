#include "../state.h"
#include "../binary.h"

int sax(struct State *state) {
    byte value = state->x & state->a;
    state->memory[state->_tmp_address] = value;
    state->negative = is_negative(value);
    state->zero = is_zero(value);
    return 0;
}
