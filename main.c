#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "opcodes.c"
#include "main.h"

byte *memory;

unsigned short program_counter;
byte stack_register;  // stack starts at $0100, ends at $01FF
byte processor_register;
byte a_register, x_register, y_register;
byte cycle_counter;

byte* init_memory() {
    // initialize 64 KB of memory
    return (byte*)calloc(MAX_MEMORY_BYTES, sizeof(byte));
}

int main() {
    memory = init_memory();

    // TODO: load something into memory here

    cycle_counter = INTERRUPT_PERIOD_MS;
    program_counter = 0;  // TODO: set initial memory location somehow

    bool is_running = true;
    while (is_running) {
        byte opcode = memory[program_counter++];  // TODO: make sure that program counter is incremented properly
        // cycle_counter -= cycles[opcode];  // TODO: define cycles

        opcodes[opcode]();

        if (cycle_counter <= 0) {
            // TODO: some interrupt tasks here

            cycle_counter += INTERRUPT_PERIOD_MS;
            // TODO: find a way to set is_running to false here when needed
            // if (can_shutdown)
            //     is_running = false;
        }
    }

    free(memory);
    return 0;
}
// int a() {
//     printf("a()\n");
//     return 0;
// }

// int b() {
//     printf("b()\n");
//     return 0;
// }

// int c() {
//     printf("c()\n");
//     return 0;
// }

// int main() {
//     int (*pointers[])(void) = { a, b, c };
//     for (int i=0; i<3; i++)
//         pointers[i]();
//     return 0;
// }