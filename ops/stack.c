#include "../state.h"

int tsx(struct State *state) {
    state->x = 0x0100 ^ state->s;
    return OK;
}

int txs(struct State *state) {
    state->s = 0x0100 ^ state->x;
    return OK;
}
