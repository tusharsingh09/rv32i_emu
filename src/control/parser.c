#include "parser.h"

static Memory memory;

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
    uint8_t opcode = parser->instrucion&0x7f;
    uint8_t* mask = &parser->instruction_mask;

    uint32_t params[5];

    switch(opcode){
        case 0b0110011: // RTYPE
            *mask = 0x0;
            break;
        case 0b0010011: // I_ALU
            *mask = 0x1;
            break;
        case 0b0000011: // I_LOAD
            *mask = 0x2;
            break;
        case 0b0100011: // STYPE
            *mask = 0x3;
            break;
        case 0b1100011: // BRANCH
            *mask = 0x4;
            break;
        case 0b1101111: // JUMP
            *mask = 0x5;
            break;
        case 0b0110111: // UTYPE
            *mask = 0x6;
            break;
        default:
            puts("Unknown instruction opcode\n");
            exit(EXIT_FAILURE);
            break;
    }
}

void parser_exec(Parser* parser, RegFile* regfile){
    uint8_t* mask = &parser->instruction_mask;
    switch(*mask){
        case R:
            exec_RType(parser->instrucion, regfile);
            puts("Exec RType\n");
            break;
        case I_ALU:
            exec_IALU(parser->instrucion, regfile);
            puts("Exec IALU\n");
            break;
        case I_LOAD:
            // exec_ILOAD(parser->instrucion, regfile);
            puts("Exec ILOAD\n");
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

// Works like a charm
void exec_RType(uint32_t instruction, RegFile* registers){
    uint32_t funct7 = (instruction&0xfe000000)>>25;
    uint32_t rs2    = (instruction&0x01f00000)>>20; // addr in reg file
    uint32_t rs1    = (instruction&0x000f8000)>>15; // addr in reg file
    uint32_t funct3 = (instruction&0x00007000)>>12;
    uint32_t rd     = (instruction&0x00000f80)>>7; // addr in reg file

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

// Also works like a charm
void exec_IALU (uint32_t instruction, RegFile* registers){
    uint16_t  imm    = ((uint32_t)(instruction&0xfff00000))>>20;
    uint8_t   rs1    = ((uint32_t)(instruction&0x000f8000))>>15; // add in reg file
    uint8_t  funct3 = (instruction&0x00007000)>>12;
    uint32_t  rd     = (instruction&0x00000f80)>>7; // addr in reg file(uint8_t)

    switch(funct3){
        case(0x0):
            registers->registers[rd] = registers->registers[rs1] + imm; // ADDI
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
    uint16_t  imm    = ((uint32_t)(instruction&0xfff00000))>>20;
    uint8_t   rs1    = ((uint32_t)(instruction&0x000f8000))>>15; // add in reg file
    uint8_t  funct3 = (instruction&0x00007000)>>12;
    uint32_t  rd     = (instruction&0x00000f80)>>7; // addr in reg file(uint8_t)

    int32_t temp;

    switch(funct3){
        case(0x0):
            temp = memory.mem[imm+registers->registers[rs1]] & 0xff;
            registers->registers[rd] = temp;
            break;
        case(0x1):
            temp = memory.mem[imm+registers->registers[rs1]] & 0xffff;
            registers->registers[rd] = temp;
            break;
        case(0x2):
            temp = memory.mem[imm+registers->registers[rs1]];
            registers->registers[rd] = temp;
            break;
        case(0x4):
            registers->registers[rd] = memory.mem[imm+registers->registers[rs1]] & 0xff;
            break;
        case(0x5):
            registers->registers[rd] = memory.mem[imm+registers->registers[rs1]] & 0xffff; 
            break;
        default:
            nop();
    }
}

// needs memory region first
void exec_S    (uint32_t instruction, RegFile* registers){
    uint32_t imm   = (instruction&0xfe000f80);
    // to join imm[11:5] and imm[4:0]
    uint8_t imm_chop1 = (imm&0xf80)>>7;
    uint16_t imm_chop2 = (imm&0xfe000000)>>20;
    imm = (imm_chop2 | (uint16_t)imm_chop1);
    printf("imm: %d\n", imm);

    uint8_t rs2    = instruction;
    uint8_t rs1    = instruction;
    uint8_t funct3 = instruction;

    switch(funct3){
        case(0x0):
            break;
        default:
            nop();
    }
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
