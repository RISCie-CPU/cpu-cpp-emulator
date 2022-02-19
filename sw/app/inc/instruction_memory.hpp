#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>

#include "consts.hpp"

enum inst_type {
    U_TYPE,
    J_TYPE,
    I_TYPE,
    B_TYPE,
    S_TYPE,
    R_TYPE,
    BREAK_TYPE
};

class DecodedInst
{
private:
    // Numbered as 31,30,29,...,2,1,0
    // Returns an integer found by reading high_bit downto low_bit
    uint32_t get_bits(int high_bit, int low_bit);


    // Returns signed integer (32-bits) / extend the sign bit to 32 bits
    // params:
    //      data - input data to sign extend
    //      data_lenght - in number of bits (ie 12)
    int32_t sign_extend(int32_t data, int32_t data_lenght);

    // Assigns all values based on instruction data and accepts instruction
    bool process_inst(uint32_t instruction_in);

    // Assigns all values based on aleady set instruction
    bool process_inst();

public:
    // Initilizes all values to Maximum uint32_t, meaning NULL
    // Also calls process_inst()
    DecodedInst(uint32_t instruction_in);
    // Initilizes all values to Maximum uint32_t, meaning Null
    DecodedInst();
    // Used for testing only, prints all values
    void print_info();

    uint32_t instruction;
    inst_type my_type;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t rd;
    uint32_t csr;
    uint32_t opcode;
    uint32_t imm;
    uint32_t func7;
    uint32_t func3;
};


class InstructionMemory
{
private:
    DecodedInst *instruction_list;

public:
    uint32_t num_instructions;

    InstructionMemory(char *file_name);
    ~InstructionMemory() = default;

    DecodedInst get_decoded_inst();
    DecodedInst get_decoded_inst(uint32_t number);
};
