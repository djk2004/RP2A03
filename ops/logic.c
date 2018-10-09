#include "../state.h"
#include "../binary.h"

int and(struct State *state, unsigned short address) {
    state->a &= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return OK;
}

int and_memory(struct State *state) {
    and(state, state->_tmp_address);
    return OK;
}

int and_immediate(struct State *state) {
    and(state, state->program_counter++);
    return OK;
}

int ora(struct State *state, unsigned short address) {
    state->a |= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return OK;
}

int ora_memory(struct State *state) {
    ora(state, state->_tmp_address);
    return OK;
}

int ora_immediate(struct State *state) {
    ora(state, state->program_counter++);
    return OK;
}

int eor(struct State *state, unsigned short address) {
    state->a ^= state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return OK;
}

int eor_memory(struct State *state) {
    eor(state, state->_tmp_address);
    return OK;
}

int eor_immediate(struct State *state) {
    eor(state, state->program_counter++);
    return OK;
}

int asl_memory(struct State *state) {
    struct Result r = shift_left_one(state->_tmp_byte);
    state->_tmp_byte = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int asl_accumulator(struct State *state) {
    struct Result r = shift_left_one(state->a);
    state->a = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int lsr_memory(struct State *state) {
    struct Result r = shift_right_one(state->_tmp_byte);
    state->_tmp_byte = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int lsr_accumulator(struct State *state) {
    struct Result r = shift_right_one(state->a);
    state->a = r.result;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int rol_memory(struct State *state) {
    struct Result r = shift_left_one(state->_tmp_byte);
    state->_tmp_byte = r.result | r.carry;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int rol_accumulator(struct State *state) {
    struct Result r = shift_left_one(state->a);
    state->a = r.result | r.carry;
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int ror_memory(struct State *state) {
    struct Result r = shift_right_one(state->_tmp_byte);
    state->_tmp_byte = r.result | (r.carry << 7);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int ror_accumulator(struct State *state) {
    struct Result r = shift_right_one(state->a);
    state->a = r.result | (r.carry << 7);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}
