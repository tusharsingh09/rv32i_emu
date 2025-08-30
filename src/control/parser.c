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
            break;
        case S:
            break;
        case B:
            break;
        case J:
            break;
        case U:
            break;
        default:
            break;
    }
}

void exec_RType(uint32_t instruction, RegFile* registers){
    uint8_t funct7 = instruction & 0xfe000000;
    uint8_t funct3 = instruction & 0x7000;
    uint8_t rd = instruction & 0xf80;
    uint8_t rs1 = registers->registers[instruction&0xf8000];
    uint8_t rs2 = registers->registers[instruction&0x1f0000];    

    switch(funct3){
        case 0x0:
            switch(funct7){
                case 0x0: // ADD
                    registers->registers[rd] = rs1 + rs2;
                    break;
                case 0x2: // SUB
                    registers->registers[rd] = rs1-rs2;
                    break;
            }
            break;

        case 0x4: // XOR
            registers->registers[rd] = rs1^rs2;
            break;

        case 0x6: // OR
            registers->registers[rd] = rs1|rs2;
            break;

        case 0x7: // AND
            registers->registers[rd] = rs1&rs2;
            break;

        case 0x1: // SLL
            registers->registers[rd] = rs1 << rs2;
            break;

        case 0x5:
            switch(funct7){
                case 0x0: // SRL
                    registers->registers[rd] = rs1 >> rs2;
                    break;

                case 0x2: // SRA
                    registers->registers[rd] = (int32_t)rs1 >> (int32_t)rs2;
                    break;
            }
            break;

        case 0x2: // SLT
            registers->registers[rd] = rs1 < rs2;
            break;
        
        case 0x3: // SLTU
            registers->registers[rd] = (uint32_t)rs1 < (uint32_t)rs2;
            break;
        
        default: // NOP
            registers->registers[rd] = registers->registers[rd];
    }
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