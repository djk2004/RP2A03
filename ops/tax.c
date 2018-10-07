#include "../state.h"

int tax(struct State *state) {
    state->x = state->a;
    state->zero = is_zero(state->x);
    state->negative = is_negative(state->x);
    return OK;
}