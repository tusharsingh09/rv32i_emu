#include <stdio.h>

#include "../dram.h"

int main(void){
    DRAM *dram;
    init_dram(&dram);
    printf("%p\n", dram);
    uint32_t a = dram_get(dram, 12);
    printf("%d\n", a);

    dram_write(dram, 12, 0xffffffab);
    a = dram_get(dram, 12);
    printf("%d\n", a);
    dram_log(dram);
    free_dram(&dram);
    return 0;
}