#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "opcodes.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s program.bin\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    uint8_t *program = malloc(size);
    if (!program) {
        perror("malloc");
        fclose(f);
        return 1;
    }
    fread(program, 1, size, f);
    fclose(f);

    long pc = 0;

    while (pc < size) {
        uint8_t opcode = program[pc++];
        switch (opcode) {
            case OPCODE_PRINT: {
                if (pc >= size) {
                    printf("Error: missing operand for PRINT\n");
                    free(program);
                    return 1;
                }
                uint8_t value = program[pc++];
                putchar(value);
                break;
            }
            case OPCODE_NEWLINE:
                putchar('\n'); 
                break;
            case OPCODE_HALT:
                free(program);
                return 0;
            default:
                printf("Unknown opcode 0x%02X at position %ld\n", opcode, pc - 1);
                free(program);
                return 1;
        }
    }

    free(program);
    return 0;
}