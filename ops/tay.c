#include "../state.h"

int tay(struct State *state) {
    state->y = state->a;
    state->zero = is_zero(state->y);
    state->negative = is_negative(state->y);
    return OK;
}