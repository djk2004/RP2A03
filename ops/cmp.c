#include "../state.h"
#include "../binary.h"

int cmp(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->a, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int cmp_memory(struct State *state) {
    cmp(state, state->_tmp_address);
    return OK;
}

int cmp_immediate(struct State *state) {
    cmp(state, state->program_counter++);
    return OK;
}
