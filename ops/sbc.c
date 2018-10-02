#include "../state.h"
#include "../binary.h"

int sbc(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->a, value, state->carry);
    state->a = r.result;
    state->carry = r.carry;
    state->overflow = r.overflow;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int sbc_memory(struct State *state) {
    sbc(state, state->_tmp_address);
    return OK;
}

int sbc_immediate(struct State *state) {
    sbc(state, state->program_counter++);
    return OK;
}
