#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 512 words in memory 32 bit each
#define MEM_END 511

typedef struct {
    uint32_t mem[MEM_END+1];
} Memory;

inline void mem_write(Memory* mem, uint16_t addr, uint32_t data){
    mem->mem[addr] = data;
}

inline uint32_t mem_read(Memory* mem, uint16_t addr){
    return mem->mem[addr];
}

void mem_log(const Memory* const mem);
void mem_clear(Memory* const mem);

#endif // MEMORY_H