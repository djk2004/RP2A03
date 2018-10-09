#include "../state.h"

int tax(struct State *state) {
    state->x = state->a;
    state->zero = is_zero(state->x);
    state->negative = is_negative(state->x);
    return OK;
}

int tay(struct State *state) {
    state->y = state->a;
    state->zero = is_zero(state->y);
    state->negative = is_negative(state->y);
    return OK;
}

int txa(struct State *state) {
    state->a = state->x;
    state->zero = is_zero(state->a);
    state->negative = is_negative(state->a);
    return OK;
}

int tya(struct State *state) {
    state->a = state->y;
    state->zero = is_zero(state->a);
    state->negative = is_negative(state->a);
    return OK;
}

int sty_memory(struct State *state) {
    state->memory[state->_tmp_address] = state->y;
    return OK;
}

int stx_memory(struct State *state) {
    state->memory[state->_tmp_address] = state->x;
    return OK;
}

int sta_memory(struct State *state) {
    state->memory[state->_tmp_address] = state->a;
    return OK;
}

int ldy(struct State *state, unsigned short address) {
    state->y = state->memory[address];
    state->negative = is_negative(state->y);
    state->zero = is_zero(state->y);
    return OK;
}

int ldy_memory(struct State *state) {
    ldy(state, state->_tmp_address);
    return OK;
}

int ldy_immediate(struct State *state) {
    ldy(state, state->program_counter++);
    return OK;
}

int ldx(struct State *state, unsigned short address) {
    state->x = state->memory[address];
    state->negative = is_negative(state->x);
    state->zero = is_zero(state->x);
    return OK;
}

int ldx_memory(struct State *state) {
    ldx(state, state->_tmp_address);
    return OK;
}

int ldx_immediate(struct State *state) {
    ldx(state, state->program_counter++);
    return OK;
}

int lda(struct State *state, unsigned short address) {
    state->a = state->memory[address];
    state->negative = is_negative(state->a);
    state->zero = is_zero(state->a);
    return OK;
}

int lda_immediate(struct State *state) {
    lda(state, state->program_counter++);
    return OK;
}

int lda_memory(struct State *state) {
    lda(state, state->_tmp_address);
    return OK;
}

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

int cpx(struct State *state, unsigned short address) {
    byte value = state->memory[address];
    struct Result r = subtract(state->x, value, 0);
    state->carry = r.carry;
    state->zero = r.zero;
    state->negative = r.negative;
    return OK;
}

int cpx_memory(struct State *state) {
    cpx(state, state->_tmp_address);
    return OK;
}

int cpx_immediate(struct State *state) {
    cpx(state, state->program_counter++);
    return OK;
}

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
