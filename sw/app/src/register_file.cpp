#include "register_file.hpp"


RegisterFile::RegisterFile()
{
    // Initialize register 0 to 0
    register_array[0].update(0);
}

void RegisterFile::Test()
{
    for (int i = 0; i < 32; i++)
        info(
            "R" << std::dec << i << std::hex << ": " << register_array[i].stored_value
        );
}

void RegisterFile::write(Emulator::Types::BUSES_t &BUS_in, int rd)
{
    // Value in register 0 must always stay 0
    if (rd != 0)
    {
        register_array[rd].update(BUS_in.WB_TO_RF);
        dbg("Register File: Writing 0x" << std::hex << BUS_in.WB_TO_RF << " --> [0x" << std::hex << rd << "]");
    }
}

void RegisterFile::read(Emulator::Types::BUSES_t &BUS_in, int rs1, int rs2)
{
    BUS_in.RF0_TO_TR0 = register_array[rs1].stored_value;
    BUS_in.RF1_TO_TR1 = register_array[rs2].stored_value;
}
