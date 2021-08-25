#include "../includes/instruction_memory.h"
#include <stdio.h>

int main (int argc, char** argv) {
    Emulator::data_t data;
    data.running = true;
    data.PC_to_IM = 0x0;

    Emulator::InstructionMemory im(argv[1], data);

    printf("0x%08x\n", data.instruction);

    im.clock_up();

    printf("0x%08x\n", data.instruction);
    return 0;
}