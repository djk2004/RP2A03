#include "../state.h"
#include "../binary.h"

int cpx(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->x, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}

int cpx_memory(struct State *state) {
    cpx(state, state->_tmp_address);
    return 0;
}

int cpx_immediate(struct State *state) {
    cpx(state, state->program_counter++);
    return 0;
}
