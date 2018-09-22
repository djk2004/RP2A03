#ifndef BINARY_H
#define BINARY_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t byte;
typedef bool bit;

extern const byte BIT_0;
extern const byte BIT_1;
extern const byte BIT_2;
extern const byte BIT_3;
extern const byte BIT_4;
extern const byte BIT_5;
extern const byte BIT_6;
extern const byte BIT_7;

bit is_negative(byte b);
byte pow2(int p);
byte twos_complement(byte b);
bit is_zero(byte b);

#endif