#include "../state.h"

int stx(struct State *state) {
    state->memory[state->_tmp_address] = state->x;
    return 0;
}
