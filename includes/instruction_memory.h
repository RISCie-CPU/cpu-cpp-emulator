#ifndef PINE_EMU_IM_H
#define PINE_EMU_IM_H

#include "types.h"
#include <string>

using namespace std;

namespace Emulator {

    using namespace Types;

    class InstructionMemory {
        private:
            string content;
            
        public:
            data_t mData;

            InstructionMemory(string file_name, data_t &data);
            void clock_up();

    };

}

#endif