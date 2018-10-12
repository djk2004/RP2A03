#include "../state.h"
#include "../binary.h"

int tsx(struct State *state) {
    state->x = 0x0100 ^ state->s;
    return OK;
}

int txs(struct State *state) {
    state->s = 0x0100 ^ state->x;
    return OK;
}

int push(struct State *state, byte b) {
    state->memory[state->s] = b;
    byte low = state->s & 0x00FF;
    struct Result r = subtract(low, 0x01, 0);
    state->s = 0x0100 | r.result;
    return OK;
}

int php(struct State *state) {
    byte status = get_processor_status(state);
    return push(state, status);
}

int pha(struct State *state) {
    return push(state, state->a);
}

int plp(struct State *state) {
    byte status = state->memory[state->s];
    state->negative = (status & BIT_7) >> 7;
    state->overflow = (status & BIT_6) >> 6;
    state->brk = (status & BIT_4) >> 4;
    state->decimal = (status & BIT_3) >> 3;
    state->interrupt_disable = (status & BIT_2) >> 2;
    state->zero = (status & BIT_1) >> 1;
    state->carry = (status & BIT_0);    
    return OK;
}

int pla(struct State *state) {
    state->a = state->memory[state->s];
    return OK;
}

int increment_stack_pointer(struct State *state) {
    byte low = 0x00FF & state->s;
    struct Result r = add(low, 0x01, 0);
    state->s = 0x0100 | r.result;
    return OK;
}
