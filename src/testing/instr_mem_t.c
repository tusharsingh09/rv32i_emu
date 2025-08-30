#include "../instruction_memory.h"

int main(void){
    InstructionMemory* instr;
    init_instr_mem(&instr);

    instr_load(instr, "instructions.hex");
    instr_log(instr);
    free_instr_mem(&instr);
    return 0;
}