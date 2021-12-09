#pragma once

#include <iostream>
#include <fstream>

#include <iostream>
#include <cmath>

#include "types.hpp"
#include "consts.hpp"

class DataMemory
{
private:
    uint8_t* ram;
    signed int sign_extend(signed int data, int data_lenght);
public:

    DataMemory();

    Emulator::Types::BUSES_t load(
        Emulator::Types::control_lines_t *control_lines_in,
        Emulator::Types::BUSES_t *BUS_in
    );

    void store(
        Emulator::Types::control_lines_t *control_lines_in,
        Emulator::Types::BUSES_t *BUS_in
    );

    void print();

};
