#pragma once

#include "types.hpp"
#include "consts.hpp"

class ControlUnit
{
private:
    // TODO
public:

    // void update_control_signals(unsigned int opcode_in);
    Emulator::Types::control_lines_t update_control_signals(
        unsigned int                     opcode_in,
        Emulator::Types::control_lines_t control_lines_in
    );
    void print_control_signals(Emulator::Types::control_lines_t control_lines_in);
};
