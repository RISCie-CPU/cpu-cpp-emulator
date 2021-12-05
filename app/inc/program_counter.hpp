#pragma once

#include <iostream>
#include <fstream>

#include "types.hpp"
#include "consts.hpp"

class ProgramCounter
{
private:
    bool logic_wire_0;
    bool SRC0;
    bool SRC1;
    bool mode;
    int current_address;
public:
    // Initialize program counter value to 0
    ProgramCounter();
    // Updates BUS lanes and latches new value if in PHASE 1 and falling edge of clock
    Emulator::Types::BUSES_t update_BUS(
        Emulator::Types::BUSES_t BUS_in,
        Emulator::Types::control_lines_t control_lines_in,
        int phase_in, int clock_in
    );
};
