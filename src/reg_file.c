#include "reg_file.h"

void reg_clear(RegFile* file){
    for(uint8_t i = 0; i<32; i++) file->registers[i] = 0;
}

void reg_write(RegFile* file, uint8_t addr, uint32_t data){
    file->registers[addr] = data;
}

uint32_t reg_file_read(RegFile* file, uint8_t addr){
    return file->registers[addr];
}

void log_registers(RegFile* file){
    char buff[10];
    FILE* f;
    f = fopen("register_data.txt", "w");
    if(!f){
        perror("Error writing register data to file");
        exit(EXIT_FAILURE);
    }
    for(uint8_t i = 0;i<32;i++){
        sprintf(buff, "%x", file->registers[i]);
        buff[9] = '\0';
        fprintf(f, "%s\n", buff);
    }
    fclose(f);
}