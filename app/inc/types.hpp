#pragma once

#include <iostream>
#include <fstream>

namespace Emulator {
namespace Types {
struct BUSES_t {
    int PC_to_IM;       // Program counter to Instruction Memory
    int IMM_TO_PC;      // Immedite generator to Program Counter
    int WB;             // Writeback
    int PC_TO_TR2;      // Program counter to Temporary register 2
    int TR2_TO_MUX;     // Temporary register 2 to multiplexer
    int TR0_TO_ALU0;    // Temporary register 0 to ALU input 0
    int MUX_TO_ALU1;    // Multiplexer output to ALU input 1
    int ALU_TO_DM;      // ALU to Data memory
    int RF0_TO_TR0;     //Register File 0 to temporary Register 0
    int RF1_TO_TR1;     // Register File 1 to temporary Register 1
};

struct control_lines_t {
    // By Control unit:
    bool IMM_GEN_CTR_0;
    bool IMM_GEN_CTR_1;
    bool IMM_GEN_CTR_2;
    bool IMM_TO_WB;
    bool ALU_TO_WB;
    bool RAM_TO_WB;
    bool ALU_SRC;
    bool STR_TO_RF;
    bool STR_TO_RAM;
    bool PC_SRC_0;
    bool PC_SRC_1;
    bool AUIPC;
    bool TAKE_BRANCH;
    // By ALU:
    bool BRANCH;
    int funct3;
    bool i;

};
}
}
