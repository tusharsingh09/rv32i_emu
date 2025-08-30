#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../reg_file.h"

typedef struct {
    uint32_t instrucion;
    uint8_t instruction_mask;
} Parser;

void parser_set_mask(Parser* parser);
void parser_exec(Parser* parser, RegFile* regfile);

#endif // PARSER_H