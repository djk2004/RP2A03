#include "../state.h"

int stx_to_tmp_address(struct State *state) {
    state->memory[state->_tmp_address] = state->x;
    return 0;
}
