#include <iostream>
#include <fstream>
#include "register.h"


Register::Register()
{
    stored_value = REG_INIT_VALUE;
}

int Register::update(int value){
    stored_value = value;
    return stored_value;
}