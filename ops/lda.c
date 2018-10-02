#include "../state.h"

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