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

void exec_RType(uint32_t instruction, RegFile* registers);
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
    uint8_t* mask = &parser->instruction_mask;
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
    uint8_t funct7 = instruction&0xfe000000;
    uint8_t rs2    = instruction&0x01f00000; // addr in reg file
    uint8_t rs1    = instruction&0x000f8000; // addr in reg file
    uint8_t funct3 = instruction&0x00007000;
    uint8_t rd     = instruction&0x00000f80; // addr in reg file
    // uint8_t opcode = instruction&0x0000007f;

    switch(funct3){
        case(0x0):{
            if(!funct7){
                registers->registers[rd] = registers->registers[rs1] + registers->registers[rs2]; // ADD
            } else if(funct7==0x20){
                registers->registers[rd] = registers->registers[rs1] - registers->registers[rs2]; // SUB
            }
            break;
        }
        case(0x4):
            registers->registers[rd] = registers->registers[rs1] ^ registers->registers[rs2]; // XOR 
            break;
        case(0x6):
            break;
            registers->registers[rd] = registers->registers[rs1] | registers->registers[rs2]; // OR
        case(0x7):
            registers->registers[rd] = registers->registers[rs1] & registers->registers[rs2]; // AND
            break;
        case(0x1):
            registers->registers[rd] = (unsigned)registers->registers[rs1] << (unsigned)registers->registers[rs2]; // SLL
            break;
        case(0x5):{
            if(funct7 == 0x0)
                registers->registers[rd] = (unsigned)registers->registers[rs1] >> (unsigned)registers->registers[rs2]; // SRL
            else if(funct7 == 0x20)
                registers->registers[rd] = (signed)registers->registers[rs1] >> (signed)registers->registers[rs2]; // SRA
            break;
        }
        case(0x2):
            registers->registers[rd] = (registers->registers[rs1] > registers->registers[rs2]);
            break;
        case(0x3):
            registers->registers[rd] = (registers->registers[rs1] < registers->registers[rs2]);
            break;
        default: nop();
    }
}

void exec_IALU (uint32_t instruction, RegFile* registers){
    uint32_t imm    = instruction&0xfff00000;
    uint8_t  rs1    = instruction&0x000f8000; // add in reg file
    uint8_t  funct3 = instruction&0x00007000;
    uint8_t  rd     = instruction&0x00000f80; // addr in reg file

    switch(funct3){
        case(0x0):
            registers->registers[rd] = registers->registers[rs1] + imm; // ADDI
            puts("ADDI\n");
            break;
        case(0x4):
            registers->registers[rd] = registers->registers[rs1] ^ imm; // XORI
            break;
        case(0x6):
            registers->registers[rd] = registers->registers[rs1] | imm; // ORI
            break;
        case(0x7):
            registers->registers[rd] = registers->registers[rs1] & imm; // ANDI
            break;
        case(0x1):
            if(!(imm&0xfe0)) registers->registers[rd] = registers->registers[rs1] << imm; // SLLI
            break;
        case(0x5):
            if(!(imm&0xfe0)) registers->registers[rd] = registers->registers[rs1] << imm; // SRI
            if(imm&0xfe0 == 0x20) registers->registers[rd] = registers->registers[rs1] >> (imm&0x1f); // SRA
            break;
        case(0x2):
            registers->registers[rd] = (registers->registers[rs1] < imm);
            break;
        case(0x3):
            registers->registers[rd] = (registers->registers[rs1] > imm);
            break;
        default:
                nop();
    }
}

void exec_ILOAD(uint32_t instruction, RegFile* registers){
    uint32_t imm   = instruction;
    uint8_t rs2    = instruction;
    uint8_t rd     = instruction;
    uint8_t funct3 = instruction;
}

void exec_S    (uint32_t instruction, RegFile* registers){
    uint32_t imm   = instruction;
    uint8_t rs2    = instruction;
    uint8_t rs1    = instruction;
    uint8_t funct3 = instruction;
}

void exec_B    (uint32_t instruction, RegFile* registers){
    uint32_t imm;
    uint8_t rs2;
    uint8_t rs1;
    uint8_t funct3;
}

void exec_J    (uint32_t instruction, RegFile* registers){
    uint32_t imm;
    uint8_t rd;
}

void exec_U    (uint32_t instruction, RegFile* registers){
    uint32_t imm;
    uint8_t rd;
}
