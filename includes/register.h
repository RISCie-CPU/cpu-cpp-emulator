#ifndef PINE_EMU_REG_H
#define PINE_EMU_REG_H

#define UNUSED_VAL 4294967295
// Could be random in future if we want to simulate real-ish conditions
#define REG_INIT_VALUE 0

class Register {
    public:
        Register();
        int stored_value;
};

#endif