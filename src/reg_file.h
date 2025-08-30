#ifndef REG_FILE_H
#define REG_FILE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint32_t registers[32];
} RegFile;

void reg_clear(RegFile* file);
void reg_write(RegFile* file, uint8_t addr, uint32_t data);
uint32_t reg_read(RegFile* file, uint8_t addr);

#endif // REG_FILE_H