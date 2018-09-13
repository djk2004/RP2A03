#include <stdio.h>
#include "opcodes.h"

int unimplemented(struct State *state) {
    printf("unimplemented opcode\n");
    return -1;
}

byte zero_page_read(struct State *state) {
    byte lowBytes = state->memory[state->program_counter++];
    state->cycles++;
    byte value = state->memory[lowBytes];
    state->cycles++;
    return value;
}

int and_zero_page(struct State *state) {
    byte value = zero_page_read(state);
    state->a &= value;
    state->negative = (state->a & 128) >> 7;
    state->zero = state->a == 0;
    return 0;
}

int lda_zero_page(struct State *state) {
    byte value = zero_page_read(state);
    state->a = value;
    state->negative = (state->a & 128) >> 7;
    state->zero = state->a == 0;
    return 0;
}

int (*opcodes[])(struct State*) = { 
    unimplemented,   // opcode 00
    unimplemented,   // opcode 01
    unimplemented,   // opcode 02
    unimplemented,   // opcode 03
    unimplemented,   // opcode 04
    unimplemented,   // opcode 05
    unimplemented,   // opcode 06
    unimplemented,   // opcode 07
    unimplemented,   // opcode 08
    unimplemented,   // opcode 09
    unimplemented,   // opcode 0A
    unimplemented,   // opcode 0B
    unimplemented,   // opcode 0C
    unimplemented,   // opcode 0D
    unimplemented,   // opcode 0E
    unimplemented,   // opcode 0F
    unimplemented,   // opcode 10
    unimplemented,   // opcode 11
    unimplemented,   // opcode 12
    unimplemented,   // opcode 13
    unimplemented,   // opcode 14
    unimplemented,   // opcode 15
    unimplemented,   // opcode 16
    unimplemented,   // opcode 17
    unimplemented,   // opcode 18
    unimplemented,   // opcode 19
    unimplemented,   // opcode 1A
    unimplemented,   // opcode 1B
    unimplemented,   // opcode 1C
    unimplemented,   // opcode 1D
    unimplemented,   // opcode 1E
    unimplemented,   // opcode 1F
    unimplemented,   // opcode 20
    unimplemented,   // opcode 21
    unimplemented,   // opcode 22
    unimplemented,   // opcode 23
    unimplemented,   // opcode 24
    and_zero_page,   // opcode 25
    unimplemented,   // opcode 26
    unimplemented,   // opcode 27
    unimplemented,   // opcode 28
    unimplemented,   // opcode 29
    unimplemented,   // opcode 2A
    unimplemented,   // opcode 2B
    unimplemented,   // opcode 2C
    unimplemented,   // opcode 2D
    unimplemented,   // opcode 2E
    unimplemented,   // opcode 2F
    unimplemented,   // opcode 30
    unimplemented,   // opcode 31
    unimplemented,   // opcode 32
    unimplemented,   // opcode 33
    unimplemented,   // opcode 34
    unimplemented,   // opcode 35
    unimplemented,   // opcode 36
    unimplemented,   // opcode 37
    unimplemented,   // opcode 38
    unimplemented,   // opcode 39
    unimplemented,   // opcode 3A
    unimplemented,   // opcode 3B
    unimplemented,   // opcode 3C
    unimplemented,   // opcode 3D
    unimplemented,   // opcode 3E
    unimplemented,   // opcode 3F
    unimplemented,   // opcode 40
    unimplemented,   // opcode 41
    unimplemented,   // opcode 42
    unimplemented,   // opcode 43
    unimplemented,   // opcode 44
    unimplemented,   // opcode 45
    unimplemented,   // opcode 46
    unimplemented,   // opcode 47
    unimplemented,   // opcode 48
    unimplemented,   // opcode 49
    unimplemented,   // opcode 4A
    unimplemented,   // opcode 4B
    unimplemented,   // opcode 4C
    unimplemented,   // opcode 4D
    unimplemented,   // opcode 4E
    unimplemented,   // opcode 4F
    unimplemented,   // opcode 50
    unimplemented,   // opcode 51
    unimplemented,   // opcode 52
    unimplemented,   // opcode 53
    unimplemented,   // opcode 54
    unimplemented,   // opcode 55
    unimplemented,   // opcode 56
    unimplemented,   // opcode 57
    unimplemented,   // opcode 58
    unimplemented,   // opcode 59
    unimplemented,   // opcode 5A
    unimplemented,   // opcode 5B
    unimplemented,   // opcode 5C
    unimplemented,   // opcode 5D
    unimplemented,   // opcode 5E
    unimplemented,   // opcode 5F
    unimplemented,   // opcode 60
    unimplemented,   // opcode 61
    unimplemented,   // opcode 62
    unimplemented,   // opcode 63
    unimplemented,   // opcode 64
    unimplemented,   // opcode 65
    unimplemented,   // opcode 66
    unimplemented,   // opcode 67
    unimplemented,   // opcode 68
    unimplemented,   // opcode 69
    unimplemented,   // opcode 6A
    unimplemented,   // opcode 6B
    unimplemented,   // opcode 6C
    unimplemented,   // opcode 6D
    unimplemented,   // opcode 6E
    unimplemented,   // opcode 6F
    unimplemented,   // opcode 70
    unimplemented,   // opcode 71
    unimplemented,   // opcode 72
    unimplemented,   // opcode 73
    unimplemented,   // opcode 74
    unimplemented,   // opcode 75
    unimplemented,   // opcode 76
    unimplemented,   // opcode 77
    unimplemented,   // opcode 78
    unimplemented,   // opcode 79
    unimplemented,   // opcode 7A
    unimplemented,   // opcode 7B
    unimplemented,   // opcode 7C
    unimplemented,   // opcode 7D
    unimplemented,   // opcode 7E
    unimplemented,   // opcode 7F
    unimplemented,   // opcode 80
    unimplemented,   // opcode 81
    unimplemented,   // opcode 82
    unimplemented,   // opcode 83
    unimplemented,   // opcode 84
    unimplemented,   // opcode 85
    unimplemented,   // opcode 86
    unimplemented,   // opcode 87
    unimplemented,   // opcode 88
    unimplemented,   // opcode 89
    unimplemented,   // opcode 8A
    unimplemented,   // opcode 8B
    unimplemented,   // opcode 8C
    unimplemented,   // opcode 8D
    unimplemented,   // opcode 8E
    unimplemented,   // opcode 8F
    unimplemented,   // opcode 90
    unimplemented,   // opcode 91
    unimplemented,   // opcode 92
    unimplemented,   // opcode 93
    unimplemented,   // opcode 94
    unimplemented,   // opcode 95
    unimplemented,   // opcode 96
    unimplemented,   // opcode 97
    unimplemented,   // opcode 98
    unimplemented,   // opcode 99
    unimplemented,   // opcode 9A
    unimplemented,   // opcode 9B
    unimplemented,   // opcode 9C
    unimplemented,   // opcode 9D
    unimplemented,   // opcode 9E
    unimplemented,   // opcode 9F
    unimplemented,   // opcode A0
    unimplemented,   // opcode A1
    unimplemented,   // opcode A2
    unimplemented,   // opcode A3
    unimplemented,   // opcode A4
    lda_zero_page,   // opcode A5
    unimplemented,   // opcode A6
    unimplemented,   // opcode A7
    unimplemented,   // opcode A8
    unimplemented,   // opcode A9
    unimplemented,   // opcode AA
    unimplemented,   // opcode AB
    unimplemented,   // opcode AC
    unimplemented,   // opcode AD
    unimplemented,   // opcode AE
    unimplemented,   // opcode AF
    unimplemented,   // opcode B0
    unimplemented,   // opcode B1
    unimplemented,   // opcode B2
    unimplemented,   // opcode B3
    unimplemented,   // opcode B4
    unimplemented,   // opcode B5
    unimplemented,   // opcode B6
    unimplemented,   // opcode B7
    unimplemented,   // opcode B8
    unimplemented,   // opcode B9
    unimplemented,   // opcode BA
    unimplemented,   // opcode BB
    unimplemented,   // opcode BC
    unimplemented,   // opcode BD
    unimplemented,   // opcode BE
    unimplemented,   // opcode BF
    unimplemented,   // opcode C0
    unimplemented,   // opcode C1
    unimplemented,   // opcode C2
    unimplemented,   // opcode C3
    unimplemented,   // opcode C4
    unimplemented,   // opcode C5
    unimplemented,   // opcode C6
    unimplemented,   // opcode C7
    unimplemented,   // opcode C8
    unimplemented,   // opcode C9
    unimplemented,   // opcode CA
    unimplemented,   // opcode CB
    unimplemented,   // opcode CC
    unimplemented,   // opcode CD
    unimplemented,   // opcode CE
    unimplemented,   // opcode CF
    unimplemented,   // opcode D0
    unimplemented,   // opcode D1
    unimplemented,   // opcode D2
    unimplemented,   // opcode D3
    unimplemented,   // opcode D4
    unimplemented,   // opcode D5
    unimplemented,   // opcode D6
    unimplemented,   // opcode D7
    unimplemented,   // opcode D8
    unimplemented,   // opcode D9
    unimplemented,   // opcode DA
    unimplemented,   // opcode DB
    unimplemented,   // opcode DC
    unimplemented,   // opcode DD
    unimplemented,   // opcode DE
    unimplemented,   // opcode DF
    unimplemented,   // opcode E0
    unimplemented,   // opcode E1
    unimplemented,   // opcode E2
    unimplemented,   // opcode E3
    unimplemented,   // opcode E4
    unimplemented,   // opcode E5
    unimplemented,   // opcode E6
    unimplemented,   // opcode E7
    unimplemented,   // opcode E8
    unimplemented,   // opcode E9
    unimplemented,   // opcode EA
    unimplemented,   // opcode EB
    unimplemented,   // opcode EC
    unimplemented,   // opcode ED
    unimplemented,   // opcode EE
    unimplemented,   // opcode EF
    unimplemented,   // opcode F0
    unimplemented,   // opcode F1
    unimplemented,   // opcode F2
    unimplemented,   // opcode F3
    unimplemented,   // opcode F4
    unimplemented,   // opcode F5
    unimplemented,   // opcode F6
    unimplemented,   // opcode F7
    unimplemented,   // opcode F8
    unimplemented,   // opcode F9
    unimplemented,   // opcode FA
    unimplemented,   // opcode FB
    unimplemented,   // opcode FC
    unimplemented,   // opcode FD
    unimplemented,   // opcode FE
    unimplemented    // opcode FF
};

int run_opcode(byte opcode, struct State* state) {
    return opcodes[opcode](state);
}
