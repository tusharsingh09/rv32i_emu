#include "instruction_memory.h"

void init_instr_mem(InstructionMemory** instr){
    *instr = (InstructionMemory*)calloc(sizeof(InstructionMemory), 1);
    (*instr)->memory = (uint32_t*)calloc(sizeof(uint32_t), MAX_INSTRUCTIONS);
    if(!(*instr)) {
        printf("Error allocating heap for instr\n");
        exit(EXIT_FAILURE);
    }
    printf("Allocated instr at: %p\n", *instr);
}

void free_instr_mem(InstructionMemory** instr){
    free(*instr);
    (*instr) = NULL;
}

void instr_load(InstructionMemory* instr, const char* file){
    uint8_t i = 0;
    FILE* fp;
#define MAX_LINE_LENGTH 11
    char line[MAX_LINE_LENGTH];
    fp = fopen(file, "r");
    if(!fp) {
        perror("couldn't find file for instructinos\n");
        exit(EXIT_FAILURE);
    }
    while(fgets(line, MAX_LINE_LENGTH, fp)){
        instr->memory[i] = (uint32_t)strtoll(line, NULL, 16);
        i++;
    }
    fclose(fp);
}

void instr_log(InstructionMemory* instr){
    for(int i=0; i<MAX_INSTRUCTIONS; i++){
        if(instr->memory[i]) printf("%x\n", instr->memory[i]);
    }
}