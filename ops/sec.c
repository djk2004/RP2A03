#include "../state.h"

int sec(struct State *state) {
    state->carry = 1;
    return OK;
}