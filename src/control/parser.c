#include "parser.h"

typedef enum {
    R = 0x0,
    I_ALU,
    I_LOAD,
    S,
    B,
    J,
    U
} INSTR_TYPE;

void exec_Rtype(uint32_t instruction, RegFile* registers);
void exec_IALU (uint32_t instruction, RegFile* registers);
void exec_ILOAD(uint32_t instruction, RegFile* registers);
void exec_S    (uint32_t instruction, RegFile* registers);
void exec_B    (uint32_t instruction, RegFile* registers);
void exec_J    (uint32_t instruction, RegFile* registers);
void exec_U    (uint32_t instruction, RegFile* registers);

inline void nop(void){
    return;
}

void parser_set_mask(Parser* parser){
    uint8_t opcode = parser->instrucion&0x3f;
    uint8_t* mask = &parser->instruction_mask;

    uint32_t params[5];

    switch(opcode){
        case R:
            *mask = 0x0;
            break;
        case I_ALU:
            *mask = 0x1;
            break;
        case I_LOAD:
            *mask = 0x2;
            break;
        case S:
            *mask = 0x3;
            break;
        case B:
            *mask = 0x4;
            break;
        case J:
            *mask = 0x5;
            break;
        case U:
            *mask = 0x6;
            break;
        default:
            *mask = I_ALU;
            break;
    }
}

void parser_exec(Parser* parser, RegFile* regfile){
    uint32_t* mask = parser->instruction_mask;
    switch(*mask){
        case R:
            exec_RType(parser->instrucion, regfile);
            break;
        case I_ALU:
            exec_IALU(parser->instrucion, regfile);
            break;
        case I_LOAD:
            exec_ILOAD(parser->instrucion, regfile);
            break;
        case S:
            exec_S(parser->instrucion, regfile);
            break;
        case B:
            exec_B(parser->instrucion, regfile);
            break;
        case J:
            exec_J(parser->instrucion, regfile);
            break;
        case U:
            exec_U(parser->instrucion, regfile);
            break;
        default:
            nop();
    }
}

void exec_RType(uint32_t instruction, RegFile* registers){
    uint8_t funct7 = instruction & 0xfe000000;
    uint8_t rs2    = instruction & 0xf8;
}

void exec_IALU (uint32_t instruction, RegFile* registers){
    
}

void exec_ILOAD(uint32_t instruction, RegFile* registers){

}

void exec_S    (uint32_t instruction, RegFile* registers){

}

void exec_B    (uint32_t instruction, RegFile* registers){

}

void exec_J    (uint32_t instruction, RegFile* registers){

}

void exec_U    (uint32_t instruction, RegFile* registers){

}