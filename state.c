#include "binary.h"
#include "state.h"

const int OK = 0;
const int OK_IGNORE_CYCLE = 1;
const int ERROR = -1;

void increment_program_counter(struct State *state) {
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
}

byte get_processor_status(struct State *state) {
    byte p = state->negative << 7;
    p |= state->overflow << 6;
    p |= 0x20;  // this bit is always 1
    p |= state->brk << 4;
    p |= state->decimal << 3;
    p |= state->interrupt_disable << 2;
    p |= state->zero << 1;
    p |= state->carry;
    return p;
}
