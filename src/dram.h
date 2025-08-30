#ifndef DRAM_H
#define DRAM_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// dual port ram
// one for writing one for reading

#ifndef DRAM_PARAMS
#define DRAM_PARAMS

// 256 words, 32 bit each, 8 bit address line
#define DRAM_SIZE 256

#endif // DRAM_PARAMS

// 2KB memory
typedef struct {
    uint32_t* memory;
} DRAM;

// initialize dram
void init_dram(DRAM** dram);
void free_dram(DRAM** dram);

uint32_t dram_get(DRAM* dram, uint8_t addr);
void dram_write(DRAM* dram, uint8_t addr, uint32_t data);

void dram_log(DRAM* dram);

#endif //  DRAM_H
