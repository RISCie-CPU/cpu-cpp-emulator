#pragma once

#include "types.h"

#define UNUSED_VAL     4294967295
// Could be random in future if we want to simulate real-ish conditions
#define REG_INIT_VALUE 0

class Register
{
    private:
    public:
        // Initialize value to REG_INIT_VALUE
        Register();
        int stored_value;
        // Updates the stored value, returns the same value (looks better in main.cpp)
        int update(int value);
};
