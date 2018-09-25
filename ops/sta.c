#include "../state.h"

int sta(struct State *state) {
    state->memory[state->_tmp_address] = state->a;
    return 0;
}
