#include "binary.h"

const byte BIT_0 = 0x01;
const byte BIT_1 = 0x02;
const byte BIT_2 = 0x04;
const byte BIT_3 = 0x08;
const byte BIT_4 = 0x10;
const byte BIT_5 = 0x20;
const byte BIT_6 = 0x40;
const byte BIT_7 = 0x80;

bit is_negative(byte b) {
    return (b & BIT_7) >> 7;
}

byte pow2(int p) {
    return BIT_0 << p;
}

byte twos_complement(byte b) {
    byte n = ~b, complement = 0;
    bit carry = 0;
    for (int i=0; i<8; i++) {
        byte mask = pow2(i);
        bit b1 = (n & mask) >> i; 
        bit b2 = (1 & mask) >> i;
        bit b1_xor_b2 = b1 ^ b2;
        bit sum = b1_xor_b2 ^ carry;
        carry = (b1 & b2) | (carry & b1_xor_b2);
        complement |= (sum << i);
    }
    return complement;
}

bit is_zero(byte b) {
    return b == 0x00;
}

struct Result add(byte value1, byte value2, bit initial_carry) {
    struct Result r = {
        .carry = 0,
        .overflow = 0,
        .zero = 0,
        .negative = 0,
        .result = initial_carry
    };
    for (int i=0; i<8; i++) {
        byte mask = pow2(i);
        bit b1 = (value1 & mask) >> i; 
        bit b2 = (value2 & mask) >> i;
        bit b1_xor_b2 = b1 ^ b2;
        bit sum = b1_xor_b2 ^ r.carry;
        r.carry = (b1 & b2) | (r.carry & b1_xor_b2);
        r.result |= (sum << i); 
        if (i == 6)
            r.overflow = r.carry;
        else if (i == 7)
            r.overflow ^= r.carry;
    }
    r.zero = is_zero(r.result);
    r.negative = is_negative(r.result);
    return r;
}

struct Result subtract(byte value1, byte value2, bit initial_carry) {
    byte value2_complement = twos_complement(value2);
    byte carry_complement = twos_complement(initial_carry);
    return add(value1, value2_complement, carry_complement);
}

struct Result shift_left_one(byte value) {
    byte new_value = value << 1;
    struct Result r = {
        .carry = (value & BIT_7) >> 7,
        .overflow = 0,
        .zero = is_zero(new_value),
        .negative = is_negative(new_value),
        .result = new_value
    };
    return r;
}

struct Result shift_right_one(byte value) {
    byte new_value = value >> 1;
    struct Result r = {
        .carry = value & BIT_0,
        .overflow = 0,
        .zero = is_zero(new_value),
        .negative = is_negative(new_value),
        .result = new_value
    };
    return r;
}