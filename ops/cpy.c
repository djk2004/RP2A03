#include "../state.h"
#include "../binary.h"

int cpy_tmp_address(struct State *state) {
    byte value = twos_complement(state->memory[state->_tmp_address]);
    bit carry = 0;
    byte diff = 0;
    for (int i=0; i<8; i++) {
        byte mask = pow2(i);
        bit b1 = (state->y & mask) >> i; 
        bit b2 = (value & mask) >> i;
        bit b1_xor_b2 = b1 ^ b2;
        bit sum = b1_xor_b2 ^ carry;
        carry = (b1 & b2) | (carry & b1_xor_b2);
        diff |= (sum << i); 
    }
    state->carry = carry;
    state->zero = is_zero(diff);
    state->negative = is_negative(diff);
    return 0;
}
