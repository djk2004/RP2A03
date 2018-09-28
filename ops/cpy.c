#include "../state.h"
#include "../binary.h"

int cpy(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->y, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return 0;
}

int cpy_zero_page(struct State *state) {
    cpy(state, state->_tmp_address);
    return 0;
}

int cpy_immediate(struct State *state) {
    cpy(state, state->program_counter++);
    return 0;
}
