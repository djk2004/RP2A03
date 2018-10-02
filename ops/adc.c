#include "../state.h"
#include "../binary.h"

int adc(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = add(state->a, value, state->carry);
    state->a = r.result;
    state->carry = r.carry;
    state->overflow = r.overflow;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int adc_memory(struct State *state) {
    adc(state, state->_tmp_address);
    return OK;
}

int adc_immediate(struct State *state) {
    adc(state, state->program_counter++);
    return OK;
}
