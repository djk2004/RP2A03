int opcode_0() {
    printf("opcode 0\n");
    return 0;
}

int opcode_1() {
    printf("opcode 1\n");
    return 0;
}

int opcode_2() {
    printf("opcode 2\n");
    return 0;
}

int (*opcodes[])(void) = { 
    opcode_0,
    opcode_1,
    opcode_2
 };