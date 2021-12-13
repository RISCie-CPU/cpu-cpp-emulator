#pragma once

#include <cstdint>

namespace Emulator {
namespace Consts {
    // Unused values
    const uint32_t UNUSED_VAL = 0xFFFFFFFF;
    // Could be random in future if we want to simulate real-ish conditions
    const uint32_t REG_INIT_VALUE = 0;
    // REMOVED FROM CODE - find a better solution! Placeholder for instruction that jumps to itself
    // const uint32_t END_INSTRUCTION = 0;
}
}
