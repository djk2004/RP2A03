#include <stdio.h>
#include <stdlib.h>
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
#include "ops/asl.h"
#include "ops/rol.h"
#include "ops/lsr.h"
#include "ops/ror.h"
#include "ops/inc.h"
#include "ops/dec.h"

int get_low_nibble_address(struct State *state) {
    byte b = state->memory[state->program_counter++];
    state->_tmp_address = b;  // resets the high nibble to 0x00
    return OK;
}

int get_high_nibble_address(struct State *state) {
    byte b = state->memory[state->program_counter++];
    state->_tmp_address ^= (b << 8);
    return OK;
}

int index_zero_page_by_x(struct State *state) {
    byte t = state->_tmp_address & 0xFF;
    state->_tmp_address = add(t, state->x, 0).result;
    return OK;
}

int index_zero_page_by_y(struct State *state) {
    byte t = state->_tmp_address & 0xFF;
    state->_tmp_address = add(t, state->y, 0).result;
    return OK;
}

int index_address_by_value(struct State *state, byte index) {
    byte low = state->_tmp_address & 0xFF;
    byte high = (state->_tmp_address & 0xFF00) >> 8;
    struct Result r = add(low, index, 0);
    state->_tmp_address = r.result;
    if (r.carry) {
        r = add(high, r.carry, 0);
        state->_tmp_address |= (r.result << 8);
        return OK;
    }
    state->_tmp_address |= (high << 8);
    return OK_IGNORE_CYCLE;    
}

int index_address_x(struct State *state) {
    return index_address_by_value(state, state->x);   
}

int index_address_y(struct State *state) {
    return index_address_by_value(state, state->y);   
}

int update_address_indirect_x(struct State *state) {
    byte a = state->_tmp_address & 0xFF;
    struct Result r = add(a, state->x, 0);
    state->_tmp_address = r.result;
    return OK;
}

int get_indirect_low_nibble(struct State *state) {
    state->_tmp_byte = state->memory[state->_tmp_address];
    return OK;
}

int get_indirect_high_nibble(struct State *state) {
    byte low = state->_tmp_address & 0xFF;
    byte lowPlus1 = add(low, 1, 0).result;
    byte high = state->memory[lowPlus1];
    state->_tmp_address = (high << 8) | state->_tmp_byte;
    return OK;
}

int read_address_contents(struct State *state) {
    state->_tmp_byte = state->memory[state->_tmp_address];
    return OK;
}

int write_value_to_address(struct State *state) {
    state->memory[state->_tmp_address] = state->_tmp_byte;
    return OK;
}

int unimplemented_message(struct State *state) {
    printf("unimplemented opcode %02X\n", state->memory[state->program_counter - 1]);
    return ERROR;
}

void unimplemented(instructions *ops) {
    int i = 0;
    ops[i++] = unimplemented_message;
    ops[i++] = NULL;
}

void indirect_x(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = update_address_indirect_x;
    ops[i++] = get_indirect_low_nibble;
    ops[i++] = get_indirect_high_nibble;
    ops[i++] = f;
    ops[i++] = NULL;
}

void zero_page(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = f;
    ops[i++] = NULL;
}

void immediate(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = f;
    ops[i++] = NULL;
}

void indirect_y(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_indirect_low_nibble;
    ops[i++] = get_indirect_high_nibble;
    ops[i++] = index_address_y;
    ops[i++] = f;
    ops[i++] = NULL;
}

void absolute(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = f;
    ops[i++] = NULL;
}

void absolute_y(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = index_address_y;
    ops[i++] = f;
    ops[i++] = NULL;
}

void absolute_x(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = index_address_x;
    ops[i++] = f;
    ops[i++] = NULL;
}

void zero_page_x_indexed(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_x;
    ops[i++] = f;
    ops[i++] = NULL;
}

void zero_page_y_indexed(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_y;
    ops[i++] = f;
    ops[i++] = NULL;
}

void zero_page_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    ops[i++] = NULL;
}

void zero_page_x_indexed_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_x;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    ops[i++] = NULL;
}

void get_opcode_instructions(instructions *ops, byte opcode) {
    switch (opcode) {
        case 0x00: { unimplemented(ops); return; }
        case 0x01: { indirect_x(ops, ora_memory); return; }
        case 0x02: { unimplemented(ops); return; }
        case 0x03: { unimplemented(ops); return; }
        case 0x04: { unimplemented(ops); return; }
        case 0x05: { zero_page(ops, ora_memory); return; }
        case 0x06: { zero_page_read_modify_write(ops, asl_memory); return; }
        case 0x07: { unimplemented(ops); return; }
        case 0x08: { unimplemented(ops); return; }
        case 0x09: { immediate(ops, ora_immediate); return; }
        case 0x0A: { immediate(ops, asl_accumulator); return; }
        case 0x0B: { unimplemented(ops); return; }
        case 0x0C: { unimplemented(ops); return; }
        case 0x0D: { absolute(ops, ora_memory); return; }
        case 0x0E: { unimplemented(ops); return; }
        case 0x0F: { unimplemented(ops); return; }
        case 0x10: { unimplemented(ops); return; }
        case 0x11: { indirect_y(ops, ora_memory); return; }
        case 0x12: { unimplemented(ops); return; }
        case 0x13: { unimplemented(ops); return; }
        case 0x14: { unimplemented(ops); return; }
        case 0x15: { zero_page_x_indexed(ops, ora_memory); return; }
        case 0x16: { zero_page_x_indexed_read_modify_write(ops, asl_memory); return; }
        case 0x17: { unimplemented(ops); return; }
        case 0x18: { unimplemented(ops); return; }
        case 0x19: { absolute_y(ops, ora_memory); return; }
        case 0x1A: { unimplemented(ops); return; }
        case 0x1B: { unimplemented(ops); return; }
        case 0x1C: { unimplemented(ops); return; }
        case 0x1D: { absolute_x(ops, ora_memory); return; }
        case 0x1E: { unimplemented(ops); return; }
        case 0x1F: { unimplemented(ops); return; }
        case 0x20: { unimplemented(ops); return; }
        case 0x21: { indirect_x(ops, and_memory); return; }
        case 0x22: { unimplemented(ops); return; }
        case 0x23: { unimplemented(ops); return; }
        case 0x24: { zero_page(ops, bit_test_memory); return; }
        case 0x25: { zero_page(ops, and_memory); return; }
        case 0x26: { zero_page_read_modify_write(ops, rol_memory); return; }
        case 0x27: { unimplemented(ops); return; }
        case 0x28: { unimplemented(ops); return; }
        case 0x29: { immediate(ops, and_immediate); return; }
        case 0x2A: { immediate(ops, rol_accumulator); return; }
        case 0x2B: { unimplemented(ops); return; }
        case 0x2C: { absolute(ops, bit_test_memory); return; }
        case 0x2D: { absolute(ops, and_memory); return; }
        case 0x2E: { unimplemented(ops); return; }
        case 0x2F: { unimplemented(ops); return; }
        case 0x30: { unimplemented(ops); return; }
        case 0x31: { indirect_y(ops, and_memory); return; }
        case 0x32: { unimplemented(ops); return; }
        case 0x33: { unimplemented(ops); return; }
        case 0x34: { unimplemented(ops); return; }
        case 0x35: { zero_page_x_indexed(ops, and_memory); return; }
        case 0x36: { zero_page_x_indexed_read_modify_write(ops, rol_memory); return; }
        case 0x37: { unimplemented(ops); return; }
        case 0x38: { unimplemented(ops); return; }
        case 0x39: { absolute_y(ops, and_memory); return; }
        case 0x3A: { unimplemented(ops); return; }
        case 0x3B: { unimplemented(ops); return; }
        case 0x3C: { unimplemented(ops); return; }
        case 0x3D: { absolute_x(ops, and_memory); return; }
        case 0x3E: { unimplemented(ops); return; }
        case 0x3F: { unimplemented(ops); return; }
        case 0x40: { unimplemented(ops); return; }
        case 0x41: { indirect_x(ops, eor_memory); return; }
        case 0x42: { unimplemented(ops); return; }
        case 0x43: { unimplemented(ops); return; }
        case 0x44: { unimplemented(ops); return; }
        case 0x45: { zero_page(ops, eor_memory); return; }
        case 0x46: { zero_page_read_modify_write(ops, lsr_memory); return; }
        case 0x47: { unimplemented(ops); return; }
        case 0x48: { unimplemented(ops); return; }
        case 0x49: { immediate(ops, eor_immediate); return; }
        case 0x4A: { immediate(ops, lsr_accumulator); return; }
        case 0x4B: { unimplemented(ops); return; }
        case 0x4C: { unimplemented(ops); return; }
        case 0x4D: { absolute(ops, eor_memory); return; }
        case 0x4E: { unimplemented(ops); return; }
        case 0x4F: { unimplemented(ops); return; }
        case 0x50: { unimplemented(ops); return; }
        case 0x51: { indirect_y(ops, eor_memory); return; }
        case 0x52: { unimplemented(ops); return; }
        case 0x53: { unimplemented(ops); return; }
        case 0x54: { unimplemented(ops); return; }
        case 0x55: { zero_page_x_indexed(ops, eor_memory); return; }
        case 0x56: { zero_page_x_indexed_read_modify_write(ops, lsr_memory); return; }
        case 0x57: { unimplemented(ops); return; }
        case 0x58: { unimplemented(ops); return; }
        case 0x59: { absolute_y(ops, eor_memory); return; }
        case 0x5A: { unimplemented(ops); return; }
        case 0x5B: { unimplemented(ops); return; }
        case 0x5C: { unimplemented(ops); return; }
        case 0x5D: { absolute_x(ops, eor_memory); return; }
        case 0x5E: { unimplemented(ops); return; }
        case 0x5F: { unimplemented(ops); return; }
        case 0x60: { unimplemented(ops); return; }
        case 0x61: { indirect_x(ops, adc_memory); return; }
        case 0x62: { unimplemented(ops); return; }
        case 0x63: { unimplemented(ops); return; }
        case 0x64: { unimplemented(ops); return; }
        case 0x65: { zero_page(ops, adc_memory); return; }
        case 0x66: { zero_page_read_modify_write(ops, ror_memory); return; }
        case 0x67: { unimplemented(ops); return; }
        case 0x68: { unimplemented(ops); return; }
        case 0x69: { immediate(ops, adc_immediate); return; }
        case 0x6A: { immediate(ops, ror_accumulator); return; }
        case 0x6B: { unimplemented(ops); return; }
        case 0x6C: { unimplemented(ops); return; }
        case 0x6D: { absolute(ops, adc_memory); return; }
        case 0x6E: { unimplemented(ops); return; }
        case 0x6F: { unimplemented(ops); return; }
        case 0x70: { unimplemented(ops); return; }
        case 0x71: { indirect_y(ops, adc_memory); return; }
        case 0x72: { unimplemented(ops); return; }
        case 0x73: { unimplemented(ops); return; }
        case 0x74: { unimplemented(ops); return; }
        case 0x75: { zero_page_x_indexed(ops, adc_memory); return; }
        case 0x76: { zero_page_x_indexed_read_modify_write(ops, ror_memory); return; }
        case 0x77: { unimplemented(ops); return; }
        case 0x78: { unimplemented(ops); return; }
        case 0x79: { absolute_y(ops, adc_memory); return; }
        case 0x7A: { unimplemented(ops); return; }
        case 0x7B: { unimplemented(ops); return; }
        case 0x7C: { unimplemented(ops); return; }
        case 0x7D: { absolute_x(ops, adc_memory); return; }
        case 0x7E: { unimplemented(ops); return; }
        case 0x7F: { unimplemented(ops); return; }
        case 0x80: { unimplemented(ops); return; }
        case 0x81: { indirect_x(ops, sta_memory); return; }
        case 0x82: { unimplemented(ops); return; }
        case 0x83: { unimplemented(ops); return; }
        case 0x84: { zero_page(ops, sty_memory); return; }
        case 0x85: { zero_page(ops, sta_memory); return; }
        case 0x86: { zero_page(ops, stx_memory); return; }
        case 0x87: { zero_page(ops, sax_memory); return; }
        case 0x88: { unimplemented(ops); return; }
        case 0x89: { unimplemented(ops); return; }
        case 0x8A: { unimplemented(ops); return; }
        case 0x8B: { unimplemented(ops); return; }
        case 0x8C: { absolute(ops, sty_memory); return; }
        case 0x8D: { absolute(ops, sta_memory); return; }
        case 0x8E: { absolute(ops, stx_memory); return; }
        case 0x8F: { unimplemented(ops); return; }
        case 0x90: { unimplemented(ops); return; }
        case 0x91: { indirect_y(ops, sta_memory); return; }
        case 0x92: { unimplemented(ops); return; }
        case 0x93: { unimplemented(ops); return; }
        case 0x94: { zero_page_x_indexed(ops, sty_memory); return; }
        case 0x95: { zero_page_x_indexed(ops, sta_memory); return; }
        case 0x96: { zero_page_y_indexed(ops, stx_memory); return; }
        case 0x97: { zero_page_y_indexed(ops, sax_memory); return; }
        case 0x98: { unimplemented(ops); return; }
        case 0x99: { absolute_y(ops, sta_memory); return; }
        case 0x9A: { unimplemented(ops); return; }
        case 0x9B: { unimplemented(ops); return; }
        case 0x9C: { unimplemented(ops); return; }
        case 0x9D: { absolute_x(ops, sta_memory); return; }
        case 0x9E: { unimplemented(ops); return; }
        case 0x9F: { unimplemented(ops); return; }
        case 0xA0: { immediate(ops, ldy_immediate); return; }
        case 0xA1: { indirect_x(ops, lda_memory); return; }
        case 0xA2: { immediate(ops, ldx_immediate); return; }
        case 0xA3: { unimplemented(ops); return; }
        case 0xA4: { zero_page(ops, ldy_memory); return; }
        case 0xA5: { zero_page(ops, lda_memory); return; }
        case 0xA6: { zero_page(ops, ldx_memory); return; }
        case 0xA7: { unimplemented(ops); return; }
        case 0xA8: { unimplemented(ops); return; }
        case 0xA9: { immediate(ops, lda_immediate); return; }
        case 0xAA: { unimplemented(ops); return; }
        case 0xAB: { unimplemented(ops); return; }
        case 0xAC: { absolute(ops, ldy_memory); return; }
        case 0xAD: { absolute(ops, lda_memory); return; }
        case 0xAE: { absolute(ops, ldx_memory); return; }
        case 0xAF: { unimplemented(ops); return; }
        case 0xB0: { unimplemented(ops); return; }
        case 0xB1: { indirect_y(ops, lda_memory); return; }
        case 0xB2: { unimplemented(ops); return; }
        case 0xB3: { unimplemented(ops); return; }
        case 0xB4: { zero_page_x_indexed(ops, ldy_memory); return; }
        case 0xB5: { zero_page_x_indexed(ops, lda_memory); return; }
        case 0xB6: { zero_page_x_indexed(ops, ldx_memory); return; }
        case 0xB7: { unimplemented(ops); return; }
        case 0xB8: { unimplemented(ops); return; }
        case 0xB9: { absolute_y(ops, lda_memory); return; }
        case 0xBA: { unimplemented(ops); return; }
        case 0xBB: { unimplemented(ops); return; }
        case 0xBC: { absolute_x(ops, ldy_memory); return; }
        case 0xBD: { absolute_x(ops, lda_memory); return; }
        case 0xBE: { absolute_x(ops, ldx_memory); return; }
        case 0xBF: { unimplemented(ops); return; }
        case 0xC0: { immediate(ops, cpy_immediate); return; }
        case 0xC1: { indirect_x(ops, cmp_memory); return; }
        case 0xC2: { unimplemented(ops); return; }
        case 0xC3: { unimplemented(ops); return; }
        case 0xC4: { zero_page(ops, cpy_memory); return; }
        case 0xC5: { zero_page(ops, cmp_memory); return; }
        case 0xC6: { zero_page_read_modify_write(ops, dec_memory); return; }
        case 0xC7: { unimplemented(ops); return; }
        case 0xC8: { unimplemented(ops); return; }
        case 0xC9: { immediate(ops, cmp_immediate); return; }
        case 0xCA: { unimplemented(ops); return; }
        case 0xCB: { unimplemented(ops); return; }
        case 0xCC: { absolute(ops, cpy_memory); return; }
        case 0xCD: { absolute(ops, cmp_memory); return; }
        case 0xCE: { unimplemented(ops); return; }
        case 0xCF: { unimplemented(ops); return; }
        case 0xD0: { unimplemented(ops); return; }
        case 0xD1: { indirect_y(ops, cmp_memory); return; }
        case 0xD2: { unimplemented(ops); return; }
        case 0xD3: { unimplemented(ops); return; }
        case 0xD4: { unimplemented(ops); return; }
        case 0xD5: { zero_page_x_indexed(ops, cmp_memory); return; }
        case 0xD6: { zero_page_x_indexed_read_modify_write(ops, dec_memory); return; }
        case 0xD7: { unimplemented(ops); return; }
        case 0xD8: { unimplemented(ops); return; }
        case 0xD9: { absolute_y(ops, cmp_memory); return; }
        case 0xDA: { unimplemented(ops); return; }
        case 0xDB: { unimplemented(ops); return; }
        case 0xDC: { unimplemented(ops); return; }
        case 0xDD: { absolute_x(ops, cmp_memory); return; }
        case 0xDE: { unimplemented(ops); return; }
        case 0xDF: { unimplemented(ops); return; }
        case 0xE0: { immediate(ops, cpx_immediate); return; }
        case 0xE1: { indirect_x(ops, sbc_memory); return; }
        case 0xE2: { unimplemented(ops); return; }
        case 0xE3: { unimplemented(ops); return; }
        case 0xE4: { zero_page(ops, cpx_memory); return; }
        case 0xE5: { zero_page(ops, sbc_memory); return; }
        case 0xE6: { zero_page_read_modify_write(ops, inc_memory); return; }
        case 0xE7: { unimplemented(ops); return; }
        case 0xE8: { unimplemented(ops); return; }
        case 0xE9: { immediate(ops, sbc_immediate); return; }
        case 0xEA: { unimplemented(ops); return; }
        case 0xEB: { unimplemented(ops); return; }
        case 0xEC: { absolute(ops, cpx_memory); return; }
        case 0xED: { absolute(ops, sbc_memory); return; }
        case 0xEE: { unimplemented(ops); return; }
        case 0xEF: { unimplemented(ops); return; }
        case 0xF0: { unimplemented(ops); return; }
        case 0xF1: { indirect_y(ops, sbc_memory); return; }
        case 0xF2: { unimplemented(ops); return; }
        case 0xF3: { unimplemented(ops); return; }
        case 0xF4: { unimplemented(ops); return; }
        case 0xF5: { zero_page_x_indexed(ops, sbc_memory); return; }
        case 0xF6: { zero_page_x_indexed_read_modify_write(ops, inc_memory); return; }
        case 0xF7: { unimplemented(ops); return; }
        case 0xF8: { unimplemented(ops); return; }
        case 0xF9: { absolute_y(ops, sbc_memory); return; }
        case 0xFA: { unimplemented(ops); return; }
        case 0xFB: { unimplemented(ops); return; }
        case 0xFC: { unimplemented(ops); return; }
        case 0xFD: { absolute_x(ops, sbc_memory); return; }
        case 0xFE: { unimplemented(ops); return; }
        case 0xFF: { unimplemented(ops); return; }
    }
    unimplemented(ops);
}
