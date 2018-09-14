#include <stdio.h>
#include "opcodes.h"

int set_negative_bit(struct State *state, byte b) {
    state->negative = (b & 128) >> 7;
    return 0;
}

int set_zero_bit(struct State *state, byte b) {
    state->zero = b == 0;
    return 0;
}

int set_zero_page_address(struct State *state) {
    state->_tmp_address = state->memory[state->program_counter++];
    return 0;
}

int unimplemented(struct State *state) {
    printf("unimplemented opcode\n");
    return -1;
}

struct Opcode unimplemented_opcode(struct State *state) {
    struct Opcode opcode = {
        .opcode = state->memory[state->program_counter - 1],
        .cycles = 1,
        .instructions = {
            unimplemented
        }
    };
    return opcode;
}

int and_zero_page(struct State *state) {
    state->a &= state->memory[state->_tmp_address];
    set_negative_bit(state, state->a);
    set_zero_bit(state, state->a);
    return 0;
}

struct Opcode and_zero_page_25(struct State *state) {
    struct Opcode opcode = {
        .opcode = 0x25,
        .cycles = 2,
        .instructions = {
            set_zero_page_address,
            and_zero_page
        }
    };
    return opcode;
}

int lda_zero_page(struct State *state) {
    state->a = state->memory[state->_tmp_address];
    set_negative_bit(state, state->a);
    set_zero_bit(state, state->a);
    return 0;
}

struct Opcode lda_zero_page_A5(struct State *state) {
    struct Opcode opcode = {
        .opcode = 0xA5,
        .cycles = 2,
        .instructions = {
            set_zero_page_address,
            lda_zero_page
        }
    };
    return opcode;
}

struct Opcode (*opcodes[])(struct State*) = { 
    unimplemented_opcode,   // opcode 00
    unimplemented_opcode,   // opcode 01
    unimplemented_opcode,   // opcode 02
    unimplemented_opcode,   // opcode 03
    unimplemented_opcode,   // opcode 04
    unimplemented_opcode,   // opcode 05
    unimplemented_opcode,   // opcode 06
    unimplemented_opcode,   // opcode 07
    unimplemented_opcode,   // opcode 08
    unimplemented_opcode,   // opcode 09
    unimplemented_opcode,   // opcode 0A
    unimplemented_opcode,   // opcode 0B
    unimplemented_opcode,   // opcode 0C
    unimplemented_opcode,   // opcode 0D
    unimplemented_opcode,   // opcode 0E
    unimplemented_opcode,   // opcode 0F
    unimplemented_opcode,   // opcode 10
    unimplemented_opcode,   // opcode 11
    unimplemented_opcode,   // opcode 12
    unimplemented_opcode,   // opcode 13
    unimplemented_opcode,   // opcode 14
    unimplemented_opcode,   // opcode 15
    unimplemented_opcode,   // opcode 16
    unimplemented_opcode,   // opcode 17
    unimplemented_opcode,   // opcode 18
    unimplemented_opcode,   // opcode 19
    unimplemented_opcode,   // opcode 1A
    unimplemented_opcode,   // opcode 1B
    unimplemented_opcode,   // opcode 1C
    unimplemented_opcode,   // opcode 1D
    unimplemented_opcode,   // opcode 1E
    unimplemented_opcode,   // opcode 1F
    unimplemented_opcode,   // opcode 20
    unimplemented_opcode,   // opcode 21
    unimplemented_opcode,   // opcode 22
    unimplemented_opcode,   // opcode 23
    unimplemented_opcode,   // opcode 24
    and_zero_page_25,
    unimplemented_opcode,   // opcode 26
    unimplemented_opcode,   // opcode 27
    unimplemented_opcode,   // opcode 28
    unimplemented_opcode,   // opcode 29
    unimplemented_opcode,   // opcode 2A
    unimplemented_opcode,   // opcode 2B
    unimplemented_opcode,   // opcode 2C
    unimplemented_opcode,   // opcode 2D
    unimplemented_opcode,   // opcode 2E
    unimplemented_opcode,   // opcode 2F
    unimplemented_opcode,   // opcode 30
    unimplemented_opcode,   // opcode 31
    unimplemented_opcode,   // opcode 32
    unimplemented_opcode,   // opcode 33
    unimplemented_opcode,   // opcode 34
    unimplemented_opcode,   // opcode 35
    unimplemented_opcode,   // opcode 36
    unimplemented_opcode,   // opcode 37
    unimplemented_opcode,   // opcode 38
    unimplemented_opcode,   // opcode 39
    unimplemented_opcode,   // opcode 3A
    unimplemented_opcode,   // opcode 3B
    unimplemented_opcode,   // opcode 3C
    unimplemented_opcode,   // opcode 3D
    unimplemented_opcode,   // opcode 3E
    unimplemented_opcode,   // opcode 3F
    unimplemented_opcode,   // opcode 40
    unimplemented_opcode,   // opcode 41
    unimplemented_opcode,   // opcode 42
    unimplemented_opcode,   // opcode 43
    unimplemented_opcode,   // opcode 44
    unimplemented_opcode,   // opcode 45
    unimplemented_opcode,   // opcode 46
    unimplemented_opcode,   // opcode 47
    unimplemented_opcode,   // opcode 48
    unimplemented_opcode,   // opcode 49
    unimplemented_opcode,   // opcode 4A
    unimplemented_opcode,   // opcode 4B
    unimplemented_opcode,   // opcode 4C
    unimplemented_opcode,   // opcode 4D
    unimplemented_opcode,   // opcode 4E
    unimplemented_opcode,   // opcode 4F
    unimplemented_opcode,   // opcode 50
    unimplemented_opcode,   // opcode 51
    unimplemented_opcode,   // opcode 52
    unimplemented_opcode,   // opcode 53
    unimplemented_opcode,   // opcode 54
    unimplemented_opcode,   // opcode 55
    unimplemented_opcode,   // opcode 56
    unimplemented_opcode,   // opcode 57
    unimplemented_opcode,   // opcode 58
    unimplemented_opcode,   // opcode 59
    unimplemented_opcode,   // opcode 5A
    unimplemented_opcode,   // opcode 5B
    unimplemented_opcode,   // opcode 5C
    unimplemented_opcode,   // opcode 5D
    unimplemented_opcode,   // opcode 5E
    unimplemented_opcode,   // opcode 5F
    unimplemented_opcode,   // opcode 60
    unimplemented_opcode,   // opcode 61
    unimplemented_opcode,   // opcode 62
    unimplemented_opcode,   // opcode 63
    unimplemented_opcode,   // opcode 64
    unimplemented_opcode,   // opcode 65
    unimplemented_opcode,   // opcode 66
    unimplemented_opcode,   // opcode 67
    unimplemented_opcode,   // opcode 68
    unimplemented_opcode,   // opcode 69
    unimplemented_opcode,   // opcode 6A
    unimplemented_opcode,   // opcode 6B
    unimplemented_opcode,   // opcode 6C
    unimplemented_opcode,   // opcode 6D
    unimplemented_opcode,   // opcode 6E
    unimplemented_opcode,   // opcode 6F
    unimplemented_opcode,   // opcode 70
    unimplemented_opcode,   // opcode 71
    unimplemented_opcode,   // opcode 72
    unimplemented_opcode,   // opcode 73
    unimplemented_opcode,   // opcode 74
    unimplemented_opcode,   // opcode 75
    unimplemented_opcode,   // opcode 76
    unimplemented_opcode,   // opcode 77
    unimplemented_opcode,   // opcode 78
    unimplemented_opcode,   // opcode 79
    unimplemented_opcode,   // opcode 7A
    unimplemented_opcode,   // opcode 7B
    unimplemented_opcode,   // opcode 7C
    unimplemented_opcode,   // opcode 7D
    unimplemented_opcode,   // opcode 7E
    unimplemented_opcode,   // opcode 7F
    unimplemented_opcode,   // opcode 80
    unimplemented_opcode,   // opcode 81
    unimplemented_opcode,   // opcode 82
    unimplemented_opcode,   // opcode 83
    unimplemented_opcode,   // opcode 84
    unimplemented_opcode,   // opcode 85
    unimplemented_opcode,   // opcode 86
    unimplemented_opcode,   // opcode 87
    unimplemented_opcode,   // opcode 88
    unimplemented_opcode,   // opcode 89
    unimplemented_opcode,   // opcode 8A
    unimplemented_opcode,   // opcode 8B
    unimplemented_opcode,   // opcode 8C
    unimplemented_opcode,   // opcode 8D
    unimplemented_opcode,   // opcode 8E
    unimplemented_opcode,   // opcode 8F
    unimplemented_opcode,   // opcode 90
    unimplemented_opcode,   // opcode 91
    unimplemented_opcode,   // opcode 92
    unimplemented_opcode,   // opcode 93
    unimplemented_opcode,   // opcode 94
    unimplemented_opcode,   // opcode 95
    unimplemented_opcode,   // opcode 96
    unimplemented_opcode,   // opcode 97
    unimplemented_opcode,   // opcode 98
    unimplemented_opcode,   // opcode 99
    unimplemented_opcode,   // opcode 9A
    unimplemented_opcode,   // opcode 9B
    unimplemented_opcode,   // opcode 9C
    unimplemented_opcode,   // opcode 9D
    unimplemented_opcode,   // opcode 9E
    unimplemented_opcode,   // opcode 9F
    unimplemented_opcode,   // opcode A0
    unimplemented_opcode,   // opcode A1
    unimplemented_opcode,   // opcode A2
    unimplemented_opcode,   // opcode A3
    unimplemented_opcode,   // opcode A4
    lda_zero_page_A5,
    unimplemented_opcode,   // opcode A6
    unimplemented_opcode,   // opcode A7
    unimplemented_opcode,   // opcode A8
    unimplemented_opcode,   // opcode A9
    unimplemented_opcode,   // opcode AA
    unimplemented_opcode,   // opcode AB
    unimplemented_opcode,   // opcode AC
    unimplemented_opcode,   // opcode AD
    unimplemented_opcode,   // opcode AE
    unimplemented_opcode,   // opcode AF
    unimplemented_opcode,   // opcode B0
    unimplemented_opcode,   // opcode B1
    unimplemented_opcode,   // opcode B2
    unimplemented_opcode,   // opcode B3
    unimplemented_opcode,   // opcode B4
    unimplemented_opcode,   // opcode B5
    unimplemented_opcode,   // opcode B6
    unimplemented_opcode,   // opcode B7
    unimplemented_opcode,   // opcode B8
    unimplemented_opcode,   // opcode B9
    unimplemented_opcode,   // opcode BA
    unimplemented_opcode,   // opcode BB
    unimplemented_opcode,   // opcode BC
    unimplemented_opcode,   // opcode BD
    unimplemented_opcode,   // opcode BE
    unimplemented_opcode,   // opcode BF
    unimplemented_opcode,   // opcode C0
    unimplemented_opcode,   // opcode C1
    unimplemented_opcode,   // opcode C2
    unimplemented_opcode,   // opcode C3
    unimplemented_opcode,   // opcode C4
    unimplemented_opcode,   // opcode C5
    unimplemented_opcode,   // opcode C6
    unimplemented_opcode,   // opcode C7
    unimplemented_opcode,   // opcode C8
    unimplemented_opcode,   // opcode C9
    unimplemented_opcode,   // opcode CA
    unimplemented_opcode,   // opcode CB
    unimplemented_opcode,   // opcode CC
    unimplemented_opcode,   // opcode CD
    unimplemented_opcode,   // opcode CE
    unimplemented_opcode,   // opcode CF
    unimplemented_opcode,   // opcode D0
    unimplemented_opcode,   // opcode D1
    unimplemented_opcode,   // opcode D2
    unimplemented_opcode,   // opcode D3
    unimplemented_opcode,   // opcode D4
    unimplemented_opcode,   // opcode D5
    unimplemented_opcode,   // opcode D6
    unimplemented_opcode,   // opcode D7
    unimplemented_opcode,   // opcode D8
    unimplemented_opcode,   // opcode D9
    unimplemented_opcode,   // opcode DA
    unimplemented_opcode,   // opcode DB
    unimplemented_opcode,   // opcode DC
    unimplemented_opcode,   // opcode DD
    unimplemented_opcode,   // opcode DE
    unimplemented_opcode,   // opcode DF
    unimplemented_opcode,   // opcode E0
    unimplemented_opcode,   // opcode E1
    unimplemented_opcode,   // opcode E2
    unimplemented_opcode,   // opcode E3
    unimplemented_opcode,   // opcode E4
    unimplemented_opcode,   // opcode E5
    unimplemented_opcode,   // opcode E6
    unimplemented_opcode,   // opcode E7
    unimplemented_opcode,   // opcode E8
    unimplemented_opcode,   // opcode E9
    unimplemented_opcode,   // opcode EA
    unimplemented_opcode,   // opcode EB
    unimplemented_opcode,   // opcode EC
    unimplemented_opcode,   // opcode ED
    unimplemented_opcode,   // opcode EE
    unimplemented_opcode,   // opcode EF
    unimplemented_opcode,   // opcode F0
    unimplemented_opcode,   // opcode F1
    unimplemented_opcode,   // opcode F2
    unimplemented_opcode,   // opcode F3
    unimplemented_opcode,   // opcode F4
    unimplemented_opcode,   // opcode F5
    unimplemented_opcode,   // opcode F6
    unimplemented_opcode,   // opcode F7
    unimplemented_opcode,   // opcode F8
    unimplemented_opcode,   // opcode F9
    unimplemented_opcode,   // opcode FA
    unimplemented_opcode,   // opcode FB
    unimplemented_opcode,   // opcode FC
    unimplemented_opcode,   // opcode FD
    unimplemented_opcode,   // opcode FE
    unimplemented_opcode    // opcode FF
};

struct Opcode run_opcode(byte opcode, struct State* state) {
    return opcodes[opcode](state);
}
