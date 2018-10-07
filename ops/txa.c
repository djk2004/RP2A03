#include "../state.h"

int txa(struct State *state) {
    state->a = state->x;
    state->zero = is_zero(state->a);
    state->negative = is_negative(state->a);
    return OK;
}