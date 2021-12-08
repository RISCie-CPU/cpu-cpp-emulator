#include "control_unit.hpp"

Emulator::Types::control_lines_t ControlUnit::update_control_signals(
    unsigned int                     opcode_in,
    Emulator::Types::control_lines_t control_lines_in
)
{
    switch (opcode_in)
    {
        case 0x33:
            // add, sub, slr, sll, xor, or, sra, and
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 1;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x03:
            // lb, lh, lw, lbu, lhu
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 1;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x13:
            // addi, slli, xori, srai, srai, srli, ori, andi
            control_lines_in.ALU_SRC       = 1;
            control_lines_in.ALU_TO_WB     = 1;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x23:
            // sb, sh, sw
            control_lines_in.ALU_SRC       = 1;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 1;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 1;
            control_lines_in.STR_TO_RF     = 0;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x63:
            // beq, bne, blt, bge, bltu, bgeu
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 1;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 1;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 0;
            control_lines_in.TAKE_BRANCH   = 1;
            break;
        case 0x37:
            // lui
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 1;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 1;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x67:
            // jalr
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 1;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 0;
            control_lines_in.PC_SRC_1      = 1;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x6F:
            // jal
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 0;
            control_lines_in.IMM_GEN_CTR_0 = 0;
            control_lines_in.IMM_GEN_CTR_1 = 0;
            control_lines_in.IMM_GEN_CTR_2 = 1;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 1;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        case 0x17:
            // auipc
            control_lines_in.ALU_SRC       = 0;
            control_lines_in.ALU_TO_WB     = 0;
            control_lines_in.AUIPC         = 1;
            control_lines_in.IMM_GEN_CTR_0 = 1;
            control_lines_in.IMM_GEN_CTR_1 = 1;
            control_lines_in.IMM_GEN_CTR_2 = 0;
            control_lines_in.IMM_TO_WB     = 0;
            control_lines_in.PC_SRC_0      = 1;
            control_lines_in.PC_SRC_1      = 0;
            control_lines_in.RAM_TO_WB     = 0;
            control_lines_in.STR_TO_RAM    = 0;
            control_lines_in.STR_TO_RF     = 1;
            control_lines_in.TAKE_BRANCH   = 0;
            break;
        default:
            std::cout << "ERROR: No opcode found" << std::endl;
    }
    return control_lines_in;
} // ControlUnit::update_control_signals

void ControlUnit::print_control_signals(
    Emulator::Types::control_lines_t control_lines_in
)
{
    // std::cout << "\n-------------------- Control signals --------------------\n";
    std::cout << "\nControl signals:" << std::endl;
    if (control_lines_in.ALU_SRC == 1) std::cout << "ALU_SRC ";
    if (control_lines_in.ALU_TO_WB == 1) std::cout << "ALU_TO_WB ";
    if (control_lines_in.AUIPC == 1) std::cout << "ALU_TO_AUIPC ";
    if (control_lines_in.IMM_GEN_CTR_0 == 1) std::cout << "IMM_GEN_CTR_0 ";
    if (control_lines_in.IMM_GEN_CTR_1 == 1) std::cout << "IMM_GEN_CTR_1 ";
    if (control_lines_in.IMM_GEN_CTR_2 == 1) std::cout << "IMM_GEN_CTR_2 ";
    if (control_lines_in.IMM_TO_WB == 1) std::cout << "IMM_TO_WB ";
    if (control_lines_in.PC_SRC_0 == 1) std::cout << "PC_SRC_0 ";
    if (control_lines_in.PC_SRC_1 == 1) std::cout << "PC_SRC_1 ";
    if (control_lines_in.RAM_TO_WB == 1) std::cout << "RAM_TO_WB ";
    if (control_lines_in.STR_TO_RAM == 1) std::cout << "STR_TO_RAM ";
    if (control_lines_in.STR_TO_RF == 1) std::cout << "STR_TO_RF ";
    if (control_lines_in.TAKE_BRANCH == 1) std::cout << "TAKE_BRANCH ";
    std::cout << "\n";
    // std::cout << "\n---------------------------------------------------------\n";
}
