#!/bin/bash
gcc -Wall main.c binary.c state.c ops/*.c opcodes.c -o main
