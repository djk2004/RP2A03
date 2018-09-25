#include <stdio.h>
#include "opcodes.h"
#include "binary.h"
#include "state.h"
#include "ops/and.h"
#include "ops/ora.h"
#include "ops/eor.h"
#include "ops/adc.h"
#include "ops/sbc.h"
#include "ops/lda.h"
#include "ops/ldx.h"
#include "ops/ldy.h"
#include "ops/stx.h"
#include "ops/sty.h"
#include "ops/sta.h"
#include "ops/bit.h"
#include "ops/cpy.h"
#include "ops/cpx.h"
#include "ops/cmp.h"
#include "ops/sax.h"

int get_zero_page_address(struct State *state) {
    state->_tmp_address = state->memory[state->program_counter++];
    return 0;
}

int index_zero_page_by_x(struct State *state) {
    byte t = 0xFF & state->_tmp_address;
    state->_tmp_address = add(t, state->x, 0).result;
    return 0;
}

int index_zero_page_by_y(struct State *state) {
    byte t = 0xFF & state->_tmp_address;
    state->_tmp_address = add(t, state->y, 0).result;
    return 0;
}

int unimplemented(struct State *state) {
    printf("unimplemented opcode\n");
    return -1;
}

instructions unimplemented_opcode = {
    unimplemented,
    NULL
};

instructions ora_zero_page_05 = {
    get_zero_page_address,
    ora_zero_page,
    NULL
};

instructions bit_test_zero_page_24 = {
    get_zero_page_address,
    bit_test_zero_page,
    NULL
};

instructions and_zero_page_25 = {
    get_zero_page_address,
    and_zero_page,
    NULL
};

instructions eor_zero_page_45 = {
    get_zero_page_address,
    eor_zero_page,
    NULL
};

instructions adc_zero_page_65 = {
    get_zero_page_address,
    adc_zero_page,
    NULL
};

instructions sty_zero_page_84 = {
    get_zero_page_address,
    sty,
    NULL
};

instructions sta_zero_page_85 = {
    get_zero_page_address,
    sta,
    NULL
};

instructions stx_zero_page_86 = {
    get_zero_page_address,
    stx,
    NULL
};

instructions sax_zero_page_87 = {
    get_zero_page_address,
    sax,
    NULL
};

instructions sty_zero_page_x_94 = {
    get_zero_page_address,
    index_zero_page_by_x,
    sty,
    NULL
};

instructions sta_zero_page_x_95 = {
    get_zero_page_address,
    index_zero_page_by_x,
    sta,
    NULL
};

instructions stx_zero_page_y_96 = {
    get_zero_page_address,
    index_zero_page_by_y,
    stx,
    NULL
};

instructions sax_zero_page_y_97 = {
    get_zero_page_address,
    index_zero_page_by_y,
    sax,
    NULL
};

instructions ldy_immediate_A0 = {
    ldy_immediate,
    NULL
};

instructions ldx_immediate_A2 = {
    ldx_immediate,
    NULL
};

instructions ldy_zero_page_A4 = {
    get_zero_page_address,
    ldy_zero_page,
    NULL
};

instructions lda_zero_page_A5 = {
    get_zero_page_address,
    lda_zero_page,
    NULL
};

instructions lda_immediate_A9 = {
    lda_immediate,
    NULL
};

instructions ldx_zero_page_A6 = {
    get_zero_page_address,
    ldx_zero_page,
    NULL
};

instructions cpy_C4 = {
    get_zero_page_address,
    cpy_zero_page,
    NULL
};

instructions cmp_C5 = {
    get_zero_page_address,
    cmp_zero_page,
    NULL
};

instructions cpx_E4 = {
    get_zero_page_address,
    cpx_zero_page,
    NULL
};

instructions sbc_zero_page_E5 = {
    get_zero_page_address,
    sbc_zero_page,
    NULL
};

instructions* get_opcode_instructions(byte opcode) {
    switch (opcode) {
        case 0x00: return &unimplemented_opcode;
        case 0x01: return &unimplemented_opcode;
        case 0x02: return &unimplemented_opcode;
        case 0x03: return &unimplemented_opcode;
        case 0x04: return &unimplemented_opcode;
        case 0x05: return &ora_zero_page_05;
        case 0x06: return &unimplemented_opcode;
        case 0x07: return &unimplemented_opcode;
        case 0x08: return &unimplemented_opcode;
        case 0x09: return &unimplemented_opcode;
        case 0x0A: return &unimplemented_opcode;
        case 0x0B: return &unimplemented_opcode;
        case 0x0C: return &unimplemented_opcode;
        case 0x0D: return &unimplemented_opcode;
        case 0x0E: return &unimplemented_opcode;
        case 0x0F: return &unimplemented_opcode;
        case 0x10: return &unimplemented_opcode;
        case 0x11: return &unimplemented_opcode;
        case 0x12: return &unimplemented_opcode;
        case 0x13: return &unimplemented_opcode;
        case 0x14: return &unimplemented_opcode;
        case 0x15: return &unimplemented_opcode;
        case 0x16: return &unimplemented_opcode;
        case 0x17: return &unimplemented_opcode;
        case 0x18: return &unimplemented_opcode;
        case 0x19: return &unimplemented_opcode;
        case 0x1A: return &unimplemented_opcode;
        case 0x1B: return &unimplemented_opcode;
        case 0x1C: return &unimplemented_opcode;
        case 0x1D: return &unimplemented_opcode;
        case 0x1E: return &unimplemented_opcode;
        case 0x1F: return &unimplemented_opcode;
        case 0x20: return &unimplemented_opcode;
        case 0x21: return &unimplemented_opcode;
        case 0x22: return &unimplemented_opcode;
        case 0x23: return &unimplemented_opcode;
        case 0x24: return &bit_test_zero_page_24;
        case 0x25: return &and_zero_page_25;
        case 0x26: return &unimplemented_opcode;
        case 0x27: return &unimplemented_opcode;
        case 0x28: return &unimplemented_opcode;
        case 0x29: return &unimplemented_opcode;
        case 0x2A: return &unimplemented_opcode;
        case 0x2B: return &unimplemented_opcode;
        case 0x2C: return &unimplemented_opcode;
        case 0x2D: return &unimplemented_opcode;
        case 0x2E: return &unimplemented_opcode;
        case 0x2F: return &unimplemented_opcode;
        case 0x30: return &unimplemented_opcode;
        case 0x31: return &unimplemented_opcode;
        case 0x32: return &unimplemented_opcode;
        case 0x33: return &unimplemented_opcode;
        case 0x34: return &unimplemented_opcode;
        case 0x35: return &unimplemented_opcode;
        case 0x36: return &unimplemented_opcode;
        case 0x37: return &unimplemented_opcode;
        case 0x38: return &unimplemented_opcode;
        case 0x39: return &unimplemented_opcode;
        case 0x3A: return &unimplemented_opcode;
        case 0x3B: return &unimplemented_opcode;
        case 0x3C: return &unimplemented_opcode;
        case 0x3D: return &unimplemented_opcode;
        case 0x3E: return &unimplemented_opcode;
        case 0x3F: return &unimplemented_opcode;
        case 0x40: return &unimplemented_opcode;
        case 0x41: return &unimplemented_opcode;
        case 0x42: return &unimplemented_opcode;
        case 0x43: return &unimplemented_opcode;
        case 0x44: return &unimplemented_opcode;
        case 0x45: return &eor_zero_page_45;
        case 0x46: return &unimplemented_opcode;
        case 0x47: return &unimplemented_opcode;
        case 0x48: return &unimplemented_opcode;
        case 0x49: return &unimplemented_opcode;
        case 0x4A: return &unimplemented_opcode;
        case 0x4B: return &unimplemented_opcode;
        case 0x4C: return &unimplemented_opcode;
        case 0x4D: return &unimplemented_opcode;
        case 0x4E: return &unimplemented_opcode;
        case 0x4F: return &unimplemented_opcode;
        case 0x50: return &unimplemented_opcode;
        case 0x51: return &unimplemented_opcode;
        case 0x52: return &unimplemented_opcode;
        case 0x53: return &unimplemented_opcode;
        case 0x54: return &unimplemented_opcode;
        case 0x55: return &unimplemented_opcode;
        case 0x56: return &unimplemented_opcode;
        case 0x57: return &unimplemented_opcode;
        case 0x58: return &unimplemented_opcode;
        case 0x59: return &unimplemented_opcode;
        case 0x5A: return &unimplemented_opcode;
        case 0x5B: return &unimplemented_opcode;
        case 0x5C: return &unimplemented_opcode;
        case 0x5D: return &unimplemented_opcode;
        case 0x5E: return &unimplemented_opcode;
        case 0x5F: return &unimplemented_opcode;
        case 0x60: return &unimplemented_opcode;
        case 0x61: return &unimplemented_opcode;
        case 0x62: return &unimplemented_opcode;
        case 0x63: return &unimplemented_opcode;
        case 0x64: return &unimplemented_opcode;
        case 0x65: return &adc_zero_page_65;
        case 0x66: return &unimplemented_opcode;
        case 0x67: return &unimplemented_opcode;
        case 0x68: return &unimplemented_opcode;
        case 0x69: return &unimplemented_opcode;
        case 0x6A: return &unimplemented_opcode;
        case 0x6B: return &unimplemented_opcode;
        case 0x6C: return &unimplemented_opcode;
        case 0x6D: return &unimplemented_opcode;
        case 0x6E: return &unimplemented_opcode;
        case 0x6F: return &unimplemented_opcode;
        case 0x70: return &unimplemented_opcode;
        case 0x71: return &unimplemented_opcode;
        case 0x72: return &unimplemented_opcode;
        case 0x73: return &unimplemented_opcode;
        case 0x74: return &unimplemented_opcode;
        case 0x75: return &unimplemented_opcode;
        case 0x76: return &unimplemented_opcode;
        case 0x77: return &unimplemented_opcode;
        case 0x78: return &unimplemented_opcode;
        case 0x79: return &unimplemented_opcode;
        case 0x7A: return &unimplemented_opcode;
        case 0x7B: return &unimplemented_opcode;
        case 0x7C: return &unimplemented_opcode;
        case 0x7D: return &unimplemented_opcode;
        case 0x7E: return &unimplemented_opcode;
        case 0x7F: return &unimplemented_opcode;
        case 0x80: return &unimplemented_opcode;
        case 0x81: return &unimplemented_opcode;
        case 0x82: return &unimplemented_opcode;
        case 0x83: return &unimplemented_opcode;
        case 0x84: return &sty_zero_page_84;
        case 0x85: return &sta_zero_page_85;
        case 0x86: return &stx_zero_page_86;
        case 0x87: return &sax_zero_page_87;
        case 0x88: return &unimplemented_opcode;
        case 0x89: return &unimplemented_opcode;
        case 0x8A: return &unimplemented_opcode;
        case 0x8B: return &unimplemented_opcode;
        case 0x8C: return &unimplemented_opcode;
        case 0x8D: return &unimplemented_opcode;
        case 0x8E: return &unimplemented_opcode;
        case 0x8F: return &unimplemented_opcode;
        case 0x90: return &unimplemented_opcode;
        case 0x91: return &unimplemented_opcode;
        case 0x92: return &unimplemented_opcode;
        case 0x93: return &unimplemented_opcode;
        case 0x94: return &sty_zero_page_x_94;
        case 0x95: return &sta_zero_page_x_95;
        case 0x96: return &stx_zero_page_y_96;
        case 0x97: return &sax_zero_page_y_97;
        case 0x98: return &unimplemented_opcode;
        case 0x99: return &unimplemented_opcode;
        case 0x9A: return &unimplemented_opcode;
        case 0x9B: return &unimplemented_opcode;
        case 0x9C: return &unimplemented_opcode;
        case 0x9D: return &unimplemented_opcode;
        case 0x9E: return &unimplemented_opcode;
        case 0x9F: return &unimplemented_opcode;
        case 0xA0: return &ldy_immediate_A0;
        case 0xA1: return &unimplemented_opcode;
        case 0xA2: return &ldx_immediate_A2;
        case 0xA3: return &unimplemented_opcode;
        case 0xA4: return &ldy_zero_page_A4;
        case 0xA5: return &lda_zero_page_A5;
        case 0xA6: return &ldx_zero_page_A6;
        case 0xA7: return &unimplemented_opcode;
        case 0xA8: return &unimplemented_opcode;
        case 0xA9: return &lda_immediate_A9;
        case 0xAA: return &unimplemented_opcode;
        case 0xAB: return &unimplemented_opcode;
        case 0xAC: return &unimplemented_opcode;
        case 0xAD: return &unimplemented_opcode;
        case 0xAE: return &unimplemented_opcode;
        case 0xAF: return &unimplemented_opcode;
        case 0xB0: return &unimplemented_opcode;
        case 0xB1: return &unimplemented_opcode;
        case 0xB2: return &unimplemented_opcode;
        case 0xB3: return &unimplemented_opcode;
        case 0xB4: return &unimplemented_opcode;
        case 0xB5: return &unimplemented_opcode;
        case 0xB6: return &unimplemented_opcode;
        case 0xB7: return &unimplemented_opcode;
        case 0xB8: return &unimplemented_opcode;
        case 0xB9: return &unimplemented_opcode;
        case 0xBA: return &unimplemented_opcode;
        case 0xBB: return &unimplemented_opcode;
        case 0xBC: return &unimplemented_opcode;
        case 0xBD: return &unimplemented_opcode;
        case 0xBE: return &unimplemented_opcode;
        case 0xBF: return &unimplemented_opcode;
        case 0xC0: return &unimplemented_opcode;
        case 0xC1: return &unimplemented_opcode;
        case 0xC2: return &unimplemented_opcode;
        case 0xC3: return &unimplemented_opcode;
        case 0xC4: return &cpy_C4;
        case 0xC5: return &cmp_C5;
        case 0xC6: return &unimplemented_opcode;
        case 0xC7: return &unimplemented_opcode;
        case 0xC8: return &unimplemented_opcode;
        case 0xC9: return &unimplemented_opcode;
        case 0xCA: return &unimplemented_opcode;
        case 0xCB: return &unimplemented_opcode;
        case 0xCC: return &unimplemented_opcode;
        case 0xCD: return &unimplemented_opcode;
        case 0xCE: return &unimplemented_opcode;
        case 0xCF: return &unimplemented_opcode;
        case 0xD0: return &unimplemented_opcode;
        case 0xD1: return &unimplemented_opcode;
        case 0xD2: return &unimplemented_opcode;
        case 0xD3: return &unimplemented_opcode;
        case 0xD4: return &unimplemented_opcode;
        case 0xD5: return &unimplemented_opcode;
        case 0xD6: return &unimplemented_opcode;
        case 0xD7: return &unimplemented_opcode;
        case 0xD8: return &unimplemented_opcode;
        case 0xD9: return &unimplemented_opcode;
        case 0xDA: return &unimplemented_opcode;
        case 0xDB: return &unimplemented_opcode;
        case 0xDC: return &unimplemented_opcode;
        case 0xDD: return &unimplemented_opcode;
        case 0xDE: return &unimplemented_opcode;
        case 0xDF: return &unimplemented_opcode;
        case 0xE0: return &unimplemented_opcode;
        case 0xE1: return &unimplemented_opcode;
        case 0xE2: return &unimplemented_opcode;
        case 0xE3: return &unimplemented_opcode;
        case 0xE4: return &cpx_E4;
        case 0xE5: return &sbc_zero_page_E5;
        case 0xE6: return &unimplemented_opcode;
        case 0xE7: return &unimplemented_opcode;
        case 0xE8: return &unimplemented_opcode;
        case 0xE9: return &unimplemented_opcode;
        case 0xEA: return &unimplemented_opcode;
        case 0xEB: return &unimplemented_opcode;
        case 0xEC: return &unimplemented_opcode;
        case 0xED: return &unimplemented_opcode;
        case 0xEE: return &unimplemented_opcode;
        case 0xEF: return &unimplemented_opcode;
        case 0xF0: return &unimplemented_opcode;
        case 0xF1: return &unimplemented_opcode;
        case 0xF2: return &unimplemented_opcode;
        case 0xF3: return &unimplemented_opcode;
        case 0xF4: return &unimplemented_opcode;
        case 0xF5: return &unimplemented_opcode;
        case 0xF6: return &unimplemented_opcode;
        case 0xF7: return &unimplemented_opcode;
        case 0xF8: return &unimplemented_opcode;
        case 0xF9: return &unimplemented_opcode;
        case 0xFA: return &unimplemented_opcode;
        case 0xFB: return &unimplemented_opcode;
        case 0xFC: return &unimplemented_opcode;
        case 0xFD: return &unimplemented_opcode;
        case 0xFE: return &unimplemented_opcode;
        case 0xFF: return &unimplemented_opcode;
    }
    return &unimplemented_opcode;
}
