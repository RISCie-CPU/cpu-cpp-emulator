#include <iostream>

#include "types.h"
#include "instruction_memory.h"
#include "control_unit.h"
#include "program_counter.h"
#include "register.h"

#define UNUSED_VAL      4294967295
#define END_INSTRUCTION 0 // Placeholder for instruction that jumps to itself

int main(int argc, char *argv[])
{
    Emulator::Types::control_lines_t control_lines;
    Emulator::Types::BUSES_t BUS;

    // Loads an instruction memory object with the file specified by the first command-line argument
    InstructionMemory Rom(argv[1]);
    ControlUnit Decoder;
    ProgramCounter Program_counter;
    Register TR0;
    Register TR1;
    Register TR2;

    // Initialize BUS lanes to 0 (More will be added)
    BUS.IMM_TO_PC = 0;
    BUS.PC_to_IM = 0;

    // Initialize basic variables
    int phase = 0;          // either 0 or 1
    int clock = 0;          // either 0 or 1

    bool running = true;

    // Main loop; one loop cycle = one clock period, PHASE = 2*clock period
    while (running){
        /*
        *       Clock is 0 for PHASE 0 or 1
        */
        clock = 0;
        std::cout << "\nPhase: " << phase << std::endl;

        int current_address = BUS.PC_to_IM;

        // Get current instruction and print its properties
        DecodedInst current_inst = Rom.get_decoded_inst(current_address >> 2);
        current_inst.print_info();

        // Stop when the instruciton jumps to itself (Had to put it here and not at the end bcs segmentation fault when it tried to read non existing instruction)
        if (current_inst.instruction == END_INSTRUCTION)
        {
            running = false;
            std::cout << "\nEnd of program." << std::endl;
            break;
        }

        // Decode current instruction into control lines and print them
        control_lines = Decoder.update_control_signals(current_inst.opcode, control_lines);
        Decoder.print_control_signals(control_lines);

        // Update program counter, in PHASE 1 it will load new value. Needs to be last
        BUS = Program_counter.update_BUS(BUS, control_lines, phase, clock);


        /*
        *       Clock is 1 for PHASE 0 or 1
        */
        clock = 1;

        // Update temporary registers:
        if (phase == 0 && clock ==1)
        {
            // TR0: TODO
            // TR1: TODO
            BUS.TR2_TO_MUX = TR2.update(BUS.PC_TO_TR2);
        }

        // Change phases (from 0 to 1, from 1 to 0)
        phase = (phase + 1) % 2;
    }
} // main