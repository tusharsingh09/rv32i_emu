#ifndef INSTR_MEM_H
#define INSTR_MEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef INSTR_MEM_PARAM
#define INSTR_MEM_PARAM

// 8 bit address bus
#define MAX_INSTRUCTIONS 256

#endif // INSTR_MEM_PARAM

typedef struct {
    uint32_t* memory;
} InstructionMemory;

void init_instr_mem(InstructionMemory** instr);
void free_instr_mem(InstructionMemory** instr);
void instr_load(InstructionMemory* instr, const char* file);
void instr_log(InstructionMemory* instr);

#endif // INSTR_MEM_H
