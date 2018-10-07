#include "../state.h"

int iny(struct State *state) {
    struct Result r = add(state->y, 0x01, 0);
    state->y = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}