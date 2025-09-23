#include "dram.h"
#include "signal.h"

void init_dram(DRAM** dram){
    // 8 bit address bus hence 256 words in dram
    *dram = (DRAM*)malloc(sizeof(DRAM));
    (*dram)->memory = (uint32_t*)calloc(DRAM_SIZE, sizeof(uint32_t));  
    if(!dram) {
        printf("Error loading DRAM\n");
        exit(EXIT_FAILURE);
    }
    printf("dram created at %p\n", dram);
}

void free_dram(DRAM** dram){
    free(*dram);
    *dram = NULL;
}

uint32_t dram_get(DRAM* dram, uint8_t addr){
    printf("getting from dram: %p\n", dram);
    return *(dram->memory+addr);
}

void dram_write(DRAM* dram, uint8_t addr, uint32_t data){
    printf("written at dram: %p\n", dram->memory+addr);
    *(dram->memory+addr) = data; 
}

void dram_log(DRAM* dram){
    FILE* fp;
    fp = fopen("dram_log.hex", "w");
    for(uint16_t i=0; i<DRAM_SIZE;i++){
        fprintf(fp, "%x\n", *(dram->memory+i));    
    }
    fclose(fp);
}
