#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dram.h"
#include "instruction_memory.h"
#include "reg_file.h"

#include "control/parser.h"

#define DEBUG

typedef struct {
    DRAM* dram;
    InstructionMemory* instr;
    RegFile regs;
    uint8_t program_counter;
    uint8_t instr_mask;
} Core;

void core_run(Core* core, Parser* parser, uint32_t clock_freq);

inline int core_step(Core* core){ core->program_counter++; return 0; }
inline int core_jump(Core* core, uint32_t addr) { core->program_counter = addr; return 0; }

int main(int argc, char** argv){
    if(argc >= 2) {
        perror("unloading\n");
        exit(EXIT_FAILURE);
    }

    Core core;
    core.program_counter = 0;
    Parser parser;
    
    init_dram(&core.dram);
    
    init_instr_mem(&core.instr);
    instr_load(core.instr, "./src/testing/instructions.hex");

#if defined(DEBUG)
    instr_log(core.instr);
#endif

    reg_clear(&core.regs);

    if(!core.dram | !core.instr) {
        perror("Failed to allocate DRAM/InstructionMemory\n");
        exit(EXIT_FAILURE);
    }

    core_run(&core, &parser, 0xffff);

    free_dram(&core.dram);
    free_instr_mem(&core.instr);

    exit(EXIT_SUCCESS);
}

void core_run(Core* core, Parser* parser, uint32_t clock_freq){
    // main execution loop
    for(uint64_t clock = 0;;clock++){
        // execute an instruction (clock occured here)
        if(clock&clock_freq){ // NOTE: Posedge occures here
            // fetch instruction
            parser->instrucion = core->instr->memory[core->program_counter];
#if defined(DEBUG)
            printf("%x : %x\n", core->program_counter, parser->instrucion);
#endif
            // execution of instruction
            parser_set_mask(parser);
            parser_exec(parser, &core->regs);

            // increase pc
            core_step(core);

            // handle branch
        }

#if defined(DEBUG)
        if(core->program_counter == 0xff) return;
#endif

    }
}