#include "../state.h"
#include "../binary.h"

int sbc_a_tmp_address(struct State *state) {
    byte value = twos_complement(state->memory[state->_tmp_address]);
    bit carry = 0, overflow = 0;
    byte new_value = twos_complement(state->carry);
    for (int i=0; i<8; i++) {
        byte mask = pow2(i);
        bit b1 = (state->a & mask) >> i; 
        bit b2 = (value & mask) >> i;
        bit b1_xor_b2 = b1 ^ b2;
        bit sum = b1_xor_b2 ^ carry;
        carry = (b1 & b2) | (carry & b1_xor_b2);
        new_value |= (sum << i); 
        if (i == 6)
            overflow = carry;
        else if (i == 7)
            overflow ^= carry;
    }

    state->a = new_value;
    state->carry = carry;
    state->overflow = overflow;
    state->zero = is_zero(state->a);
    state->negative = is_negative(state->a);
    return 0;
}
