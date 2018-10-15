#include <stdio.h>
#include <stdlib.h>
#include "opcodes.h"
#include "binary.h"
#include "state.h"
#include "ops/arithmetic.h"
#include "ops/branch.h"
#include "ops/flags.h"
#include "ops/logic.h"
#include "ops/registers.h"
#include "ops/stack.h"
#include "ops/unsupported.h"

int get_low_nibble_address(struct State *state) {
    byte b = state->memory[state->program_counter];
    increment_program_counter(state);
    state->_tmp_address = b;  // resets the high nibble to 0x00
    return OK;
}

int get_high_nibble_address(struct State *state) {
    byte b = state->memory[state->program_counter];
    increment_program_counter(state);
    state->_tmp_address |= (b << 8);
    return OK;
}

int get_high_nibble_address_to_pc(struct State *state) {
    byte b = state->memory[state->program_counter];
    increment_program_counter(state);
    state->_tmp_address |= (b << 8);
    state->program_counter = state->_tmp_address;
    return OK;
}

int set_tmp_address_contents_to_pc(struct State *state) {
    state->program_counter = state->memory[state->_tmp_address];
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

int index_address_by_value(struct State *state, byte index, bool ignore_cycle_on_no_carry) {
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
    return ignore_cycle_on_no_carry ? OK_IGNORE_CYCLE : OK;
}

int index_address_x(struct State *state) {
    return index_address_by_value(state, state->x, true);   
}

int index_address_y(struct State *state) {
    return index_address_by_value(state, state->y, true);   
}

int index_address_x_always_cycle(struct State *state) {
    return index_address_by_value(state, state->x, false);   
}

int index_address_y_always_cycle(struct State *state) {
    return index_address_by_value(state, state->y, false);   
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

int push_pc_high_nibble(struct State *state) {
    state->brk = 1;
    byte pch = (state->program_counter & 0xFF00) >> 8;
    return push(state, pch);
}

int push_pc_low_nibble(struct State *state) {
    byte pch = state->program_counter & 0x00FF;
    return push(state, pch);
}

int brk_fetch_pcl(struct State *state) {
    byte low = state->memory[0xFFFE];
    state->program_counter = low;
    return OK;
}

int brk_fetch_pch(struct State *state) {
    byte high = state->memory[0xFFFF];
    state->program_counter |= (high << 8);
    return OK;
}

int pull_pc_low_nibble(struct State *state) {
    byte low = pull(state);
    state->program_counter = low;
    return OK;
}

int peek_pc_high_nibble(struct State *state) {
    byte high = peek(state);
    state->program_counter |= high << 8;
    return OK;
}

int nop(struct State *state) {
    // do nothing
    return OK;
}

int unimplemented_message(struct State *state) {
    printf("unimplemented opcode\n");
    return ERROR;
}

int unimplemented(instructions *ops) {
    int i = 0;
    ops[i++] = unimplemented_message;
    return i;
}

int indirect_x(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = update_address_indirect_x;
    ops[i++] = get_indirect_low_nibble;
    ops[i++] = get_indirect_high_nibble;
    ops[i++] = f;
    return i;
}

int zero_page(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = f;
    return i;
}

int immediate(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = f;
    return i;
}

int indirect_y(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_indirect_low_nibble;
    ops[i++] = get_indirect_high_nibble;
    ops[i++] = index_address_y;
    ops[i++] = f;
    return i;
}

int jmp_absolute(instructions *ops) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address_to_pc;
    return i;
}

int jmp_indirect(instructions *ops) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = nop;
    ops[i++] = set_tmp_address_contents_to_pc;
    return i;
}

int absolute(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = f;
    return i;
}

int absolute_y(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = index_address_y;
    ops[i++] = f;
    return i;
}

int absolute_x(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = index_address_x;
    ops[i++] = f;
    return i;
}

int zero_page_x_indexed(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_x;
    ops[i++] = f;
    return i;
}

int zero_page_y_indexed(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_y;
    ops[i++] = f;
    return i;
}

int zero_page_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    return i;
}

int zero_page_x_indexed_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = index_zero_page_by_x;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    return i;
}

int absolute_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    return i;
}

int absolute_x_indexed_read_modify_write(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = get_high_nibble_address;
    ops[i++] = index_address_x_always_cycle;
    ops[i++] = read_address_contents;
    ops[i++] = f;
    ops[i++] = write_value_to_address;
    return i;
}

int push_on_stack(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = nop;
    ops[i++] = f;
    return i;
}

int pull_from_stack(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = nop;
    ops[i++] = increment_stack_pointer;
    ops[i++] = f;
    return i;
}

int brk(instructions *ops) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = push_pc_high_nibble;
    ops[i++] = push_pc_low_nibble;
    ops[i++] = php;
    ops[i++] = brk_fetch_pcl;
    ops[i++] = brk_fetch_pch;
    return i;
}

int jsr(instructions *ops) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = nop;
    ops[i++] = push_pc_high_nibble;
    ops[i++] = push_pc_low_nibble;
    ops[i++] = get_high_nibble_address_to_pc;
    return i;
}

int rts(instructions *ops) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = increment_stack_pointer;
    ops[i++] = pull_pc_low_nibble;
    ops[i++] = peek_pc_high_nibble;
    ops[i++] = increment_program_counter;
    return i;
}

int branch_on_false(struct State *state) {
    bit is_condition_true = 0x01 & state->_tmp_byte;
    if (is_condition_true) {
        return OK_IGNORE_CYCLE;
    }
    // At this point, the branch statement will end, and the program counter will automatically
    // increment to the next opcode
    return OK_IGNORE_AND_BREAK;
}

int branch_on_true(struct State *state) {
    byte pcl = 0x00FF & state->program_counter;
    byte offset = 0x00FF & state->_tmp_address;
    struct Result r = add(pcl, offset, 0);
    state->program_counter = (0xFF00 & state->program_counter) | r.result;
    state->_tmp_byte = r.carry;
    return OK;
}

int branch_fix_pc_high_nibble(struct State *state) {
    bit carry = 0x01 & state->_tmp_byte;
    if (carry) {
        byte pch = (0xFF00 & state->program_counter) >> 8;
        struct Result r = add(pch, 0x01, 0);
        state->program_counter = (r.result << 8) | (state->program_counter & 0x00FF);
    } else {
        state->_tmp_byte = 0x00;
        increment_program_counter(state);
    }
    return OK;
}

int branch_on_next_page(struct State *state) {
    bit crossed_page_boundary = 0x01 & state->_tmp_byte;
    if (crossed_page_boundary) {
        increment_program_counter(state);
    }
    return OK;
}

int branch(instructions *ops, int f(struct State *state)) {
    int i = 0;
    ops[i++] = get_low_nibble_address;
    ops[i++] = f;
    ops[i++] = branch_on_false;
    ops[i++] = branch_on_true;
    ops[i++] = branch_fix_pc_high_nibble;
    ops[i++] = branch_on_next_page;
    return i;  
}

int get_opcode_instructions(instructions *ops, byte opcode) {
    switch (opcode) {
        case 0x00: { return brk(ops); }
        case 0x01: { return indirect_x(ops, ora_memory); }
        case 0x02: { return unimplemented(ops); }
        case 0x03: { return unimplemented(ops); }
        case 0x04: { return unimplemented(ops); }
        case 0x05: { return zero_page(ops, ora_memory); }
        case 0x06: { return zero_page_read_modify_write(ops, asl_memory); }
        case 0x07: { return unimplemented(ops); }
        case 0x08: { return push_on_stack(ops, php); }
        case 0x09: { return immediate(ops, ora_immediate); }
        case 0x0A: { return immediate(ops, asl_accumulator); }
        case 0x0B: { return unimplemented(ops); }
        case 0x0C: { return unimplemented(ops); }
        case 0x0D: { return absolute(ops, ora_memory); }
        case 0x0E: { return absolute_read_modify_write(ops, asl_memory); }
        case 0x0F: { return unimplemented(ops); }
        case 0x10: { return branch(ops, bpl); }
        case 0x11: { return indirect_y(ops, ora_memory); }
        case 0x12: { return unimplemented(ops); }
        case 0x13: { return unimplemented(ops); }
        case 0x14: { return unimplemented(ops); }
        case 0x15: { return zero_page_x_indexed(ops, ora_memory); }
        case 0x16: { return zero_page_x_indexed_read_modify_write(ops, asl_memory); }
        case 0x17: { return unimplemented(ops); }
        case 0x18: { return immediate(ops, clc); }
        case 0x19: { return absolute_y(ops, ora_memory); }
        case 0x1A: { return unimplemented(ops); }
        case 0x1B: { return unimplemented(ops); }
        case 0x1C: { return unimplemented(ops); }
        case 0x1D: { return absolute_x(ops, ora_memory); }
        case 0x1E: { return absolute_x_indexed_read_modify_write(ops, asl_memory); }
        case 0x1F: { return unimplemented(ops); }
        case 0x20: { return jsr(ops); }
        case 0x21: { return indirect_x(ops, and_memory); }
        case 0x22: { return unimplemented(ops); }
        case 0x23: { return unimplemented(ops); }
        case 0x24: { return zero_page(ops, bit_test_memory); }
        case 0x25: { return zero_page(ops, and_memory); }
        case 0x26: { return zero_page_read_modify_write(ops, rol_memory); }
        case 0x27: { return unimplemented(ops); }
        case 0x28: { return pull_from_stack(ops, plp); }
        case 0x29: { return immediate(ops, and_immediate); }
        case 0x2A: { return immediate(ops, rol_accumulator); }
        case 0x2B: { return unimplemented(ops); }
        case 0x2C: { return absolute(ops, bit_test_memory); }
        case 0x2D: { return absolute(ops, and_memory); }
        case 0x2E: { return absolute_read_modify_write(ops, rol_memory); }
        case 0x2F: { return unimplemented(ops); }
        case 0x30: { return branch(ops, bmi); }
        case 0x31: { return indirect_y(ops, and_memory); }
        case 0x32: { return unimplemented(ops); }
        case 0x33: { return unimplemented(ops); }
        case 0x34: { return unimplemented(ops); }
        case 0x35: { return zero_page_x_indexed(ops, and_memory); }
        case 0x36: { return zero_page_x_indexed_read_modify_write(ops, rol_memory); }
        case 0x37: { return unimplemented(ops); }
        case 0x38: { return immediate(ops, sec); }
        case 0x39: { return absolute_y(ops, and_memory); }
        case 0x3A: { return unimplemented(ops); }
        case 0x3B: { return unimplemented(ops); }
        case 0x3C: { return unimplemented(ops); }
        case 0x3D: { return absolute_x(ops, and_memory); }
        case 0x3E: { return absolute_x_indexed_read_modify_write(ops, rol_memory); }
        case 0x3F: { return unimplemented(ops); }
        case 0x40: { return unimplemented(ops); }
        case 0x41: { return indirect_x(ops, eor_memory); }
        case 0x42: { return unimplemented(ops); }
        case 0x43: { return unimplemented(ops); }
        case 0x44: { return unimplemented(ops); }
        case 0x45: { return zero_page(ops, eor_memory); }
        case 0x46: { return zero_page_read_modify_write(ops, lsr_memory); }
        case 0x47: { return unimplemented(ops); }
        case 0x48: { return push_on_stack(ops, pha); }
        case 0x49: { return immediate(ops, eor_immediate); }
        case 0x4A: { return immediate(ops, lsr_accumulator); }
        case 0x4B: { return unimplemented(ops); }
        case 0x4C: { return jmp_absolute(ops); }
        case 0x4D: { return absolute(ops, eor_memory); }
        case 0x4E: { return absolute_read_modify_write(ops, lsr_memory); }
        case 0x4F: { return unimplemented(ops); }
        case 0x50: { return branch(ops, bvc); }
        case 0x51: { return indirect_y(ops, eor_memory); }
        case 0x52: { return unimplemented(ops); }
        case 0x53: { return unimplemented(ops); }
        case 0x54: { return unimplemented(ops); }
        case 0x55: { return zero_page_x_indexed(ops, eor_memory); }
        case 0x56: { return zero_page_x_indexed_read_modify_write(ops, lsr_memory); }
        case 0x57: { return unimplemented(ops); }
        case 0x58: { return immediate(ops, cli); }
        case 0x59: { return absolute_y(ops, eor_memory); }
        case 0x5A: { return unimplemented(ops); }
        case 0x5B: { return unimplemented(ops); }
        case 0x5C: { return unimplemented(ops); }
        case 0x5D: { return absolute_x(ops, eor_memory); }
        case 0x5E: { return absolute_x_indexed_read_modify_write(ops, lsr_memory); }
        case 0x5F: { return unimplemented(ops); }
        case 0x60: { return rts(ops); }
        case 0x61: { return indirect_x(ops, adc_memory); }
        case 0x62: { return unimplemented(ops); }
        case 0x63: { return unimplemented(ops); }
        case 0x64: { return unimplemented(ops); }
        case 0x65: { return zero_page(ops, adc_memory); }
        case 0x66: { return zero_page_read_modify_write(ops, ror_memory); }
        case 0x67: { return unimplemented(ops); }
        case 0x68: { return pull_from_stack(ops, pla); }
        case 0x69: { return immediate(ops, adc_immediate); }
        case 0x6A: { return immediate(ops, ror_accumulator); }
        case 0x6B: { return unimplemented(ops); }
        case 0x6C: { return jmp_indirect(ops); }
        case 0x6D: { return absolute(ops, adc_memory); }
        case 0x6E: { return absolute_read_modify_write(ops, ror_memory); }
        case 0x6F: { return unimplemented(ops); }
        case 0x70: { return branch(ops, bvs); }
        case 0x71: { return indirect_y(ops, adc_memory); }
        case 0x72: { return unimplemented(ops); }
        case 0x73: { return unimplemented(ops); }
        case 0x74: { return unimplemented(ops); }
        case 0x75: { return zero_page_x_indexed(ops, adc_memory); }
        case 0x76: { return zero_page_x_indexed_read_modify_write(ops, ror_memory); }
        case 0x77: { return unimplemented(ops); }
        case 0x78: { return immediate(ops, sei); }
        case 0x79: { return absolute_y(ops, adc_memory); }
        case 0x7A: { return unimplemented(ops); }
        case 0x7B: { return unimplemented(ops); }
        case 0x7C: { return unimplemented(ops); }
        case 0x7D: { return absolute_x(ops, adc_memory); }
        case 0x7E: { return absolute_x_indexed_read_modify_write(ops, ror_memory); }
        case 0x7F: { return unimplemented(ops); }
        case 0x80: { return unimplemented(ops); }
        case 0x81: { return indirect_x(ops, sta_memory); }
        case 0x82: { return unimplemented(ops); }
        case 0x83: { return unimplemented(ops); }
        case 0x84: { return zero_page(ops, sty_memory); }
        case 0x85: { return zero_page(ops, sta_memory); }
        case 0x86: { return zero_page(ops, stx_memory); }
        case 0x87: { return zero_page(ops, sax_memory); }
        case 0x88: { return immediate(ops, dey); }
        case 0x89: { return unimplemented(ops); }
        case 0x8A: { return immediate(ops, txa); }
        case 0x8B: { return unimplemented(ops); }
        case 0x8C: { return absolute(ops, sty_memory); }
        case 0x8D: { return absolute(ops, sta_memory); }
        case 0x8E: { return absolute(ops, stx_memory); }
        case 0x8F: { return unimplemented(ops); }
        case 0x90: { return branch(ops, bcc); }
        case 0x91: { return indirect_y(ops, sta_memory); }
        case 0x92: { return unimplemented(ops); }
        case 0x93: { return unimplemented(ops); }
        case 0x94: { return zero_page_x_indexed(ops, sty_memory); }
        case 0x95: { return zero_page_x_indexed(ops, sta_memory); }
        case 0x96: { return zero_page_y_indexed(ops, stx_memory); }
        case 0x97: { return zero_page_y_indexed(ops, sax_memory); }
        case 0x98: { return immediate(ops, tya); }
        case 0x99: { return absolute_y(ops, sta_memory); }
        case 0x9A: { return immediate(ops, txs); }
        case 0x9B: { return unimplemented(ops); }
        case 0x9C: { return unimplemented(ops); }
        case 0x9D: { return absolute_x(ops, sta_memory); }
        case 0x9E: { return unimplemented(ops); }
        case 0x9F: { return unimplemented(ops); }
        case 0xA0: { return immediate(ops, ldy_immediate); }
        case 0xA1: { return indirect_x(ops, lda_memory); }
        case 0xA2: { return immediate(ops, ldx_immediate); }
        case 0xA3: { return unimplemented(ops); }
        case 0xA4: { return zero_page(ops, ldy_memory); }
        case 0xA5: { return zero_page(ops, lda_memory); }
        case 0xA6: { return zero_page(ops, ldx_memory); }
        case 0xA7: { return unimplemented(ops); }
        case 0xA8: { return immediate(ops, tay); }
        case 0xA9: { return immediate(ops, lda_immediate); }
        case 0xAA: { return immediate(ops, tax); }
        case 0xAB: { return unimplemented(ops); }
        case 0xAC: { return absolute(ops, ldy_memory); }
        case 0xAD: { return absolute(ops, lda_memory); }
        case 0xAE: { return absolute(ops, ldx_memory); }
        case 0xAF: { return unimplemented(ops); }
        case 0xB0: { return branch(ops, bcs); }
        case 0xB1: { return indirect_y(ops, lda_memory); }
        case 0xB2: { return unimplemented(ops); }
        case 0xB3: { return unimplemented(ops); }
        case 0xB4: { return zero_page_x_indexed(ops, ldy_memory); }
        case 0xB5: { return zero_page_x_indexed(ops, lda_memory); }
        case 0xB6: { return zero_page_y_indexed(ops, ldx_memory); }
        case 0xB7: { return unimplemented(ops); }
        case 0xB8: { return immediate(ops, clv); }
        case 0xB9: { return absolute_y(ops, lda_memory); }
        case 0xBA: { return immediate(ops, tsx); }
        case 0xBB: { return unimplemented(ops); }
        case 0xBC: { return absolute_x(ops, ldy_memory); }
        case 0xBD: { return absolute_x(ops, lda_memory); }
        case 0xBE: { return absolute_y(ops, ldx_memory); }
        case 0xBF: { return unimplemented(ops); }
        case 0xC0: { return immediate(ops, cpy_immediate); }
        case 0xC1: { return indirect_x(ops, cmp_memory); }
        case 0xC2: { return unimplemented(ops); }
        case 0xC3: { return unimplemented(ops); }
        case 0xC4: { return zero_page(ops, cpy_memory); }
        case 0xC5: { return zero_page(ops, cmp_memory); }
        case 0xC6: { return zero_page_read_modify_write(ops, dec); }
        case 0xC7: { return unimplemented(ops); }
        case 0xC8: { return immediate(ops, iny); }
        case 0xC9: { return immediate(ops, cmp_immediate); }
        case 0xCA: { return immediate(ops, dex); }
        case 0xCB: { return unimplemented(ops); }
        case 0xCC: { return absolute(ops, cpy_memory); }
        case 0xCD: { return absolute(ops, cmp_memory); }
        case 0xCE: { return absolute_read_modify_write(ops, dec); }
        case 0xCF: { return unimplemented(ops); }
        case 0xD0: { return branch(ops, bne); }
        case 0xD1: { return indirect_y(ops, cmp_memory); }
        case 0xD2: { return unimplemented(ops); }
        case 0xD3: { return unimplemented(ops); }
        case 0xD4: { return unimplemented(ops); }
        case 0xD5: { return zero_page_x_indexed(ops, cmp_memory); }
        case 0xD6: { return zero_page_x_indexed_read_modify_write(ops, dec); }
        case 0xD7: { return unimplemented(ops); }
        case 0xD8: { return immediate(ops, cld); }
        case 0xD9: { return absolute_y(ops, cmp_memory); }
        case 0xDA: { return unimplemented(ops); }
        case 0xDB: { return unimplemented(ops); }
        case 0xDC: { return unimplemented(ops); }
        case 0xDD: { return absolute_x(ops, cmp_memory); }
        case 0xDE: { return absolute_x_indexed_read_modify_write(ops, dec); }
        case 0xDF: { return unimplemented(ops); }
        case 0xE0: { return immediate(ops, cpx_immediate); }
        case 0xE1: { return indirect_x(ops, sbc_memory); }
        case 0xE2: { return unimplemented(ops); }
        case 0xE3: { return unimplemented(ops); }
        case 0xE4: { return zero_page(ops, cpx_memory); }
        case 0xE5: { return zero_page(ops, sbc_memory); }
        case 0xE6: { return zero_page_read_modify_write(ops, inc); }
        case 0xE7: { return unimplemented(ops); }
        case 0xE8: { return immediate(ops, inx); }
        case 0xE9: { return immediate(ops, sbc_immediate); }
        case 0xEA: { return immediate(ops, nop); }
        case 0xEB: { return unimplemented(ops); }
        case 0xEC: { return absolute(ops, cpx_memory); }
        case 0xED: { return absolute(ops, sbc_memory); }
        case 0xEE: { return absolute_read_modify_write(ops, inc); }
        case 0xEF: { return unimplemented(ops); }
        case 0xF0: { return branch(ops, beq); }
        case 0xF1: { return indirect_y(ops, sbc_memory); }
        case 0xF2: { return unimplemented(ops); }
        case 0xF3: { return unimplemented(ops); }
        case 0xF4: { return unimplemented(ops); }
        case 0xF5: { return zero_page_x_indexed(ops, sbc_memory); }
        case 0xF6: { return zero_page_x_indexed_read_modify_write(ops, inc); }
        case 0xF7: { return unimplemented(ops); }
        case 0xF8: { return immediate(ops, sed); }
        case 0xF9: { return absolute_y(ops, sbc_memory); }
        case 0xFA: { return unimplemented(ops); }
        case 0xFB: { return unimplemented(ops); }
        case 0xFC: { return unimplemented(ops); }
        case 0xFD: { return absolute_x(ops, sbc_memory); }
        case 0xFE: { return absolute_x_indexed_read_modify_write(ops, inc); }
        case 0xFF: { return unimplemented(ops); }
    }
    return unimplemented(ops);
}
