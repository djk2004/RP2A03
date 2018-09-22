#include "../state.h"

int sty_to_tmp_address(struct State *state) {
    state->memory[state->_tmp_address] = state->y;
    return 0;
}
