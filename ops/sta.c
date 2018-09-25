#include "../state.h"

int sta_zero_page(struct State *state) {
    state->memory[state->_tmp_address] = state->a;
    return 0;
}
