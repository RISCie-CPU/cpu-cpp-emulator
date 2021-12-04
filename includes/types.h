#ifndef PINE_EMU_TYPES_H
#define PINE_EMU_TYPES_H

#include <inttypes.h>

namespace Emulator {

    namespace Types {

        struct data_t {
            int PC_to_IM;
            uint32_t instruction;
            bool running;
        };

        struct control_lines_t {
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
        };

    }

}

#endif