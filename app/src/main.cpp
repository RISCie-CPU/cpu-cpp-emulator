#include "types.h"
#include "instruction_memory.h"
#include "control_unit.h"
#include "program_counter.h"
#include <iostream>

#define UNUSED_VAL 4294967295
#define END_INSTRUCTION 0       // Placeholder for instruction that jumps to itself

int main(int argc, char *argv[])
{
    Emulator::Types::control_lines_t control_lines;

    //Loads an instruction memory object with the file specified by the first command-line argument
    InstructionMemory Rom(argv[1]);
    ControlUnit Decoder;
    ProgramCounter Program_counter;

    /*
                    Testing only
    */

    // Cycles through each instruction to print it's information
    for(int i=0; i<Rom.num_instructions; i++){
        DecodedInst current_inst = Rom.get_decoded_inst(i);
        current_inst.print_info();

        control_lines = Decoder.update_control_signals(current_inst.opcode, control_lines);
        Decoder.print_control_signals(control_lines);
    }



    /*
                    REAL(ish)
    */

    // int phase = 0;          // either 0 or 1
    // int clock_counter = 0;

    // bool running = true;

    // while (running){
    //     int current_address = Program_counter.current_address;

    //     DecodedInst current_inst = Rom.get_decoded_inst(current_address >> 2);
    //     current_inst.print_info();

    //     // control_lines = Decoder.update_control_signals(current_inst.opcode, control_lines);
    //     // Decoder.print_control_signals(control_lines);

    //     if (current_inst.instruction == END_INSTRUCTION)
    //     {
    //         running = false;
    //     }

    // }
}

