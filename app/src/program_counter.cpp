#include "program_counter.hpp"


ProgramCounter::ProgramCounter()
{
    current_address = 0;
}

Emulator::Types::BUSES_t ProgramCounter::update_BUS(
    Emulator::Types::BUSES_t BUS_in,
    Emulator::Types::control_lines_t control_lines_in,
    int phase_in, int clock_in
)
{
    std::cout << "PC update" << std::endl;
    logic_wire_0 = ((control_lines_in.AUIPC & (phase_in == 0)) | (!control_lines_in.AUIPC & (phase_in == 1)));

    SRC0 = control_lines_in.PC_SRC_0 & logic_wire_0;
    SRC1 = control_lines_in.PC_SRC_1 & logic_wire_0;
    mode = (!control_lines_in.TAKE_BRANCH & SRC0) | (control_lines_in.BRANCH & control_lines_in.TAKE_BRANCH);

    int output_address;
    // std::cout << "1: " << std::hex << current_address << std::endl;
    // Program counter + 4
    if (mode == 0) output_address = current_address + 4;
    // std::cout << "2: " << std::hex << output_address << std::endl;
    // Program counter + Immediate value
    if (mode == 1) output_address = current_address + BUS_in.IMM_TO_PC;
    if (SRC1 == 0) BUS_in.PC_TO_TR2 = output_address;
    if (SRC1 == 1) BUS_in.PC_TO_TR2 = BUS_in.WB;
    // std::cout << "To TR0: 0x" << std::hex << BUS_in.PC_TO_TR2 << std::endl;;
    // std::cout << "3: " << std::hex << output_address << std::endl;


    // Store new value on falling edge of CLK1
    if (clock_in == 0 && phase_in == 1)
    {
        current_address = BUS_in.PC_TO_TR2;
        BUS_in.PC_to_IM = current_address;
        std::cout << "New PC value: " << std::hex << current_address << std::endl;

        // TODO: repeated code, space for optimization
        // Program counter + 4
        if (mode == 0) output_address = current_address + 4;
        // Program counter + Immediate value
        if (mode == 1) output_address = current_address + BUS_in.IMM_TO_PC;
    }

    return BUS_in;
} // ProgramCounter::update_BUS
