#include "../state.h"

int sty_memory(struct State *state) {
    state->memory[state->_tmp_address] = state->y;
    return OK;
}
