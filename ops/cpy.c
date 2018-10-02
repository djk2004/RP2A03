#include "../state.h"
#include "../binary.h"

int cpy(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->y, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int cpy_memory(struct State *state) {
    cpy(state, state->_tmp_address);
    return OK;
}

int cpy_immediate(struct State *state) {
    cpy(state, state->program_counter++);
    return OK;
}
