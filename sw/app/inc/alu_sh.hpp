#pragma once

#include "types.hpp"
#include "consts.hpp"

class ALU_SH
{
private:
public:
    // Initialize value to REG_INIT_VALUE
    ALU_SH();
    void update(Emulator::Types::BUSES_t *BUS_in, Emulator::Types::control_lines_t &control_lines_in);
};
