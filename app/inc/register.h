#pragma once

#include "types.h"
#include "consts.h"


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
