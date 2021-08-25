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

    }

}

#endif