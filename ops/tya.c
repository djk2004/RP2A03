#include "../state.h"

int tya(struct State *state) {
    state->a = state->y;
    state->zero = is_zero(state->a);
    state->negative = is_negative(state->a);
    return OK;
}