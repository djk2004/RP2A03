#include "../state.h"

int sta_to_tmp_address(struct State *state) {
    state->memory[state->_tmp_address] = state->a;
    return 0;
}
