#include "binary.h"
#include "state.h"

const int OK = 0;
const int OK_IGNORE_CYCLE = 1;
const int ERROR = -1;

int increment_program_counter(struct State *state) {
    byte low = 0x00FF & state->program_counter;
    struct Result r = add(low, 0x01, 0);
    if (r.carry) {
        low = r.result;
        byte high = state->program_counter >> 8;
        r = add(high, 0x01, 0);
        state->program_counter = (r.result << 8) | low;
    } else {
        state->program_counter = (state->program_counter & 0xFF00) | r.result;
    }
    return state->program_counter;
}