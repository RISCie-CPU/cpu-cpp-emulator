#include "../includes/instruction_memory.h"
#include<iostream>
#include<fstream>

string readfile(const char* inputFile) {
    ifstream in_file(inputFile, ios::binary);
    string out = "";
    char c;

    while (in_file.get(c)) {
        out += c;
    }

    if (out.substr(0, 3) == "\xEF\xBB\xBF") out = out.substr(3);

    return out;
}

char* string_to_chr_array(string str) {
    char* writable = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), writable);
    writable[str.size()] = '\0'; // don't forget the terminating 0

    return writable;
}

namespace Emulator {

    InstructionMemory::InstructionMemory(string file_name, data_t &data) {
        content = readfile(file_name.c_str());
        mData = data;
    }

    void InstructionMemory::clock_up() {
        char* file_bytes = string_to_chr_array(content);
        int address = mData.PC_to_IM / 4;


        if (address >= content.length() / 4) {
            printf("DEBUG: address %i, length %i\n", address, content.length());
            throw;
        }

        mData.instruction = (uint32_t) *(file_bytes + (address * 4)) +
            (*(file_bytes + 1 + (address * 4)) << 8) +
            (*(file_bytes + 2 + (address * 4)) << 16) +
            (*(file_bytes + 3 + (address * 4)) << 24);

        if (mData.instruction == 0x6f) {
            mData.running = false;
        }

        printf("0x%08x\n", mData.instruction);
    }
}