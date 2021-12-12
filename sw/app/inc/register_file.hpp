#pragma once

#include <iostream>
#include <fstream>

#include "types.hpp"
#include "consts.hpp"
#include "register.hpp"
#include "instruction_memory.hpp"

class RegisterFile
{
private:
    Register register_array[32];
public:
    // Initialize program counter value to 0
    RegisterFile();
    void Test();
    
    void write(Emulator::Types::BUSES_t &BUS_in,int rd);

    void read(Emulator::Types::BUSES_t &BUS_in,int rs1, int rs2);
};