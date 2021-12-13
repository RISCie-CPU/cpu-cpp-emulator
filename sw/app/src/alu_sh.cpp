#include "alu_sh.hpp"

/*
 *  Inputs:
 *      - X - 32b input data
 *      - Y - 32b input data
 *      - i - 31. bit in instruction
 *      - funct3:
 *          000: add ('i' = 0)
 *          000: sub ('i' = 1)
 *          001: sll
 *          010: slt (set if less than) (if true, then output = 1)
 *          011: sltu (set if less than unsigned) (if true, then output = 1)
 *          100: xor
 *          101: srl ('i' = 0)
 *          101: sra ('i' = 1)
 *          110: or
 *          111: and
 *      - funct3; comparison: (setting 'branch' signal if true)
 *          000: beq (branch if equal)
 *          001: bne (branch if not equal)
 *          100: blt (branch if less than)
 *          101: bge (branch if greater or equal)
 *          110: bltu (branch if less than unsigned)
 *          111: bgeu (branch if greater or equal unsigned)
 *  Outputs:
 *      - result - 32b ouptut
 *      - branch - 1b, confirmation of conditional jump
 *
 */

ALU_SH::ALU_SH()
{ }

void ALU_SH::update(Emulator::Types::BUSES_t *BUS_in, Emulator::Types::control_lines_t &control_lines_in)
{
    int operand_x = (*BUS_in).TR0_TO_ALU0;
    int operand_y = (*BUS_in).ALU_MUX_TO_ALU1;
    int funct3    = control_lines_in.funct3;
    // int funct3 = 0;
    bool i    = control_lines_in.i;
    bool mode = control_lines_in.TAKE_BRANCH;

    bool alu_op_0 = !(control_lines_in.STR_TO_RAM | control_lines_in.RAM_TO_WB);
    bool alu_op_1 = !(control_lines_in.ALU_SRC);

    int temp_output  = 0;
    bool temp_branch = 0;

    if (alu_op_0 == 0) funct3 = 0;
    if (alu_op_1 == 0) i = 0;
    // std::cout << " ---- ALU ----" <<std::endl;
    // std::cout << "X: 0x" << std::hex << (*BUS_in).TR0_TO_ALU0 << std::endl;
    // std::cout << "Y: 0x" << std::hex << (*BUS_in).ALU_MUX_TO_ALU1 << std::endl;
    // std::cout << "funct3: 0x" << std::hex << funct3 << std::endl;
    // std::cout << "i: 0x" << std::hex << i << std::endl;
    // std::cout << "mode: 0x" << std::hex << mode << std::endl;
    // std::cout << "ALU OP 0: 0x" << std::hex << alu_op_0 << std::endl;
    // std::cout << "ALU OP 1: 0x" << std::hex << alu_op_1 << std::endl;


    if (funct3 == 0b000)
    {
        // add
        if (i == 0) temp_output = (operand_x + operand_y) & 0xffffffff;
        // sub
        else if (i == 1) temp_output = (operand_x - operand_y) & 0xffffffff;
        // beq
        if (operand_x == operand_y) temp_branch = 1;
        // std::cout << "XX: " << te
    }
    else if (funct3 == 0b001)
    {
        // bne
        if (operand_x != operand_y) temp_branch = 1;
    }
    // slt
    else if (funct3 == 0b010)
    {
        if (operand_x < operand_y) temp_output = 1;
    }
    // sltu
    else if (funct3 == 0b011)
    {
        if ((unsigned int) operand_x < (unsigned int) operand_y) temp_output = 1;
    }
    // XOR
    else if (funct3 == 0b100)
    {
        temp_output = operand_x ^ operand_y;
        // blt
        if (operand_x < operand_y) temp_branch = 1;
    }
    else if (funct3 == 0b101)
    {
        // bge
        if (operand_x >= operand_y) temp_branch = 1;
    }
    // or
    else if (funct3 == 0b110)
    {
        temp_output = operand_x | operand_y;
        // bltu
        if (operand_x <= operand_y) temp_branch = 1;
    }
    // and
    else if (funct3 == 0b111)
    {
        temp_output = operand_x & operand_y;
        // bgeu
        if ((unsigned int) operand_x >= (unsigned int) operand_y) temp_branch = 1;
    }

    // Shifter
    // WARNING: do not merge control_lines_in.funct3 and func3! they are different for alu and shifter. Same with i.

    // sll
    if (control_lines_in.funct3 == 0b001)
    {
        temp_output = (unsigned int) operand_x << ((unsigned int) operand_y & 0b11111);
    }
    else if (control_lines_in.funct3 == 0b101)
    {
        // srl
        if (control_lines_in.i == 0)
        {
            temp_output = (unsigned int) operand_x >> ((unsigned int) operand_y & 0b11111);
        }
        // sra
        else
        {
            temp_output = operand_x >> ((unsigned int) operand_y & 0b11111);
        }
    }

    // Output

    if (mode == 0) // Normal ALU operation
    {   // std::cout << "ALU output: " << std::hex << temp_output << std::endl;
        (*BUS_in).ALU_TO_DM     = temp_output;
        control_lines_in.BRANCH = 0;
    }
    else // Calculating if condition is true or not for conditional jump
    {   // std::cout << "Branch bit: " << temp_branch << std::endl;
        (*BUS_in).ALU_TO_DM     = 0;
        control_lines_in.BRANCH = temp_branch;
    }
} // ALU_SH::update
