#include "data_memory.hpp"
#include "debug.hpp"

void DataMemory::print()
{
    for (int i = 0; i < 40 * 4; i += 4)
    {
        std::cout << i << "[" << (int) ram[i + 3] << (int) ram[i + 2] << (int) ram[i + 1] << (int) ram[i] << "] ";
    }
    std::cout << "\n";
}

DataMemory::DataMemory()
{
    ram       = new uint8_t[131072 * 4];
    video_ram = new uint8_t[3750];
}


signed int DataMemory::sign_extend(signed int data, int data_lenght)
{
    // 32-12 = 20
    int remaining_bits = 32 - data_lenght;
    int mask = pow(2, data_lenght) - 1;

    signed int sign_extended_data = (data & mask) << remaining_bits;
    sign_extended_data >>= remaining_bits;

    return sign_extended_data;
}

Emulator::Types::BUSES_t DataMemory::load(Emulator::Types::control_lines_t *control_lines_in, Emulator::Types::BUSES_t *BUS_in)
{
    int output;
    int addr = (*BUS_in).ALU_TO_DM;
    unsigned int funct3 = (*control_lines_in).funct3;
    // By bytes (lb):
    if (funct3 == 0b000)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr   = addr % 524288; // 2 ** 19
            output = sign_extend(ram[addr], 8);
            dbg("Data memory: lb, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")");
        }
        // VRAM

        // Special registers
        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }
    }
    // By halfs (lh):
    if (funct3 == 0b001)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr    = addr % 524288; // 2 ** 19
            output  = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            output  = sign_extend(output, 16);
            dbg("Data memory: lh, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")");
        }
        // VRAM

        // Special registers
        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }
    }
    // By words (lw):
    if (funct3 == 0b010)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            output  = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            output |= ram[addr + 2] << 16;
            output |= ram[addr + 3] << 24;
            dbg("Data memory: lw, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")");
        }
        // VRAM

        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }
    }
    // By bytes unsigned (lbu):
    if (funct3 == 0b100)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr   = addr % 524288; // 2 ** 19
            output = sign_extend(ram[addr], 8);
            dbg("Data memory: lbu, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")");
        }
        // VRAM

        // Special registers
        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }

        //Keyboard Memory Location
        if(addr==0x80000004){
            output = 0x32;
        }
    }
    // By halfes unsigned (lhu):
    if (funct3 == 0b101)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr    = addr % 524288; // 2 ** 19
            output  = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            dbg("Data memory: lhu, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")");
        }
        // VRAM

        // Special registers
        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }
    }

    (*BUS_in).WB = output;
    // std::cout << "Data memory: 0x" << std::hex << output << " to WB" << std::endl;
    // std::cout << "ram[0x7fe88]: 0x" << std::hex << (int)ram[0x7fe88+3] << std::hex << (int)ram[0x7fe88+2] << std::hex << (int)ram[0x7fe88+1] << std::hex << (int)ram[0x7fe88] << std::endl;
    return *BUS_in;
} // DataMemory::load

void DataMemory::store(Emulator::Types::control_lines_t *control_lines_in, Emulator::Types::BUSES_t *BUS_in)
{
    int to_store        = (*BUS_in).TR1_TO_RAMD;
    int addr            = (*BUS_in).ALU_TO_DM;
    unsigned int funct3 = (*control_lines_in).funct3;

    // By bytes (sb):
    if (funct3 == 0b000)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr      = addr % 524288; // 2 ** 19
            ram[addr] = to_store & 0xff;
            dbg("Data memory: sb, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]");
        }
        else if (addr >> 30 == 1)
        {
            // VRAM
            addr = addr % 8192; // 2 ** 13
            video_ram[addr] = to_store & 0xff;
        }

        // Special registers
    }
    // By halfs (sh):
    if (funct3 == 0b001)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr = addr % 524288; // 2 ** 19
            ram[addr + 0] = (to_store & 0x00ff) >> 0;
            ram[addr + 1] = (to_store & 0xff00) >> 8;
            dbg("Data memory: sh, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]");
        }
        else if (addr >> 30 == 1)
        {
            // VRAM
            addr = addr % 8192; // 2 ** 13
            video_ram[addr + 0] = (to_store & 0x00ff) >> 0;
            video_ram[addr + 1] = (to_store & 0xff00) >> 8;
        }

        // Special registers
    }
    // By words (sw):
    if (funct3 == 0b010)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr = addr % 524288; // 2 ** 19
            ram[addr + 0] = (to_store & 0x000000ff) >> 0;
            ram[addr + 1] = (to_store & 0x0000ff00) >> 8;
            ram[addr + 2] = (to_store & 0x00ff0000) >> 16;
            ram[addr + 3] = (to_store & 0xff000000) >> 24;
            dbg("Data memory: sw, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]");
        }
        else if (addr >> 30 == 1)
        {
            // VRAM
            addr = addr % 8192; // 2 ** 13
            video_ram[addr + 0] = (to_store & 0x000000ff) >> 0;
            video_ram[addr + 1] = (to_store & 0x0000ff00) >> 8;
            video_ram[addr + 2] = (to_store & 0x00ff0000) >> 16;
            video_ram[addr + 3] = (to_store & 0xff000000) >> 24;
        }

        // Special registers
    }
} // DataMemory::store