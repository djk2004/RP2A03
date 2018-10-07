#include "../state.h"

int inx(struct State *state) {
    struct Result r = add(state->x, 0x01, 0);
    state->x = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}