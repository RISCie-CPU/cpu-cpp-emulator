#include "../includes/instruction_memory.h"
#include <iostream>

#define UNUSED_VAL 4294967295


int main(int argc, char *argv[])
{   
    //Loads an instruction memory object with the file specified by the first command-line argument
    InstructionMemory Rom(argv[1]);

    // Cycles through each instruction to print it's information
    // Used for testing only
    for(int i=0; i<Rom.num_instructions; i++){
        Rom.get_decoded_inst(i).print_info();
    }
}
