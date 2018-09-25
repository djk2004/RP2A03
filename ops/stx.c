#include "../state.h"

int stx_zero_page(struct State *state) {
    state->memory[state->_tmp_address] = state->x;
    return 0;
}
