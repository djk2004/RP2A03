#include "../state.h"

int sty_zero_page(struct State *state) {
    state->memory[state->_tmp_address] = state->y;
    return 0;
}
