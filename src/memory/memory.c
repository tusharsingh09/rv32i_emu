#include "memory.h"

void mem_log(const Memory* const mem){
    FILE* fp;
    char buff[10];
    fp = fopen("memory_data.txt", "w");
    if(!fp){
        printf("faield to create file for memoery logging/\n");
        exit(EXIT_FAILURE);
    }
    for(uint16_t i = 0; i < MEM_END; i++){
        sprintf(buff, "%x", mem->mem[i]);
        buff[9] = '\0';
        fprintf(fp, "%s\n", buff);
    }
    fclose(fp);
}

void mem_clear(Memory* const mem){
    for(uint16_t i = 0; i < MEM_END; i++){
        mem->mem[i] = 0;
    }
}