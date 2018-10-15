#include "../state.h"
#include "../binary.h"

int bpl(struct State *state) {
    state->_tmp_byte = state->negative == 0;
    return OK_IGNORE_CYCLE;
}

int bmi(struct State *state) {
    state->_tmp_byte = state->negative == 1;
    return OK_IGNORE_CYCLE;
}

int bvc(struct State *state) {
    state->_tmp_byte = state->overflow == 0;
    return OK_IGNORE_CYCLE;
}

int bvs(struct State *state) {
    state->_tmp_byte = state->overflow == 1;
    return OK_IGNORE_CYCLE;
}

int bcc(struct State *state) {
    state->_tmp_byte = state->carry == 0;
    return OK_IGNORE_CYCLE;
}

int bcs(struct State *state) {
    state->_tmp_byte = state->carry == 1;
    return OK_IGNORE_CYCLE;
}

int bne(struct State *state) {
    state->_tmp_byte = state->zero == 0;
    return OK_IGNORE_CYCLE;
}

int beq(struct State *state) {
    state->_tmp_byte = state->zero == 1;
    return OK_IGNORE_CYCLE;
}
