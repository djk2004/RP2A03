#include "../state.h"

int stx_memory(struct State *state) {
    state->memory[state->_tmp_address] = state->x;
    return 0;
}
