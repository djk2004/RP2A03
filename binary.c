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
