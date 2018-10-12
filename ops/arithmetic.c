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
    adc(state, increment_program_counter(state));
    return OK;
}

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
    sbc(state, increment_program_counter(state));
    return OK;
}

int inc(struct State *state) {
    struct Result r = add(state->_tmp_byte, 0x01, 0);
    state->_tmp_byte = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int inx(struct State *state) {
    struct Result r = add(state->x, 0x01, 0);
    state->x = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int iny(struct State *state) {
    struct Result r = add(state->y, 0x01, 0);
    state->y = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int dec(struct State *state) {
    struct Result r = subtract(state->_tmp_byte, 0x01, 0);
    state->_tmp_byte = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int dex(struct State *state) {
    struct Result r = subtract(state->x, 0x01, 0);
    state->x = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int dey(struct State *state) {
    struct Result r = subtract(state->y, 0x01, 0);
    state->y = r.result;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}