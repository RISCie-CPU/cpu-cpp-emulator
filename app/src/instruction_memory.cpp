#include "instruction_memory.h"
#include<iostream>
#include<fstream>
#include<cmath>

const char *type_words[]={
    "U_TYPE",
    "J_TYPE",
    "I_TYPE",
    "B_TYPE",
    "S_TYPE",
    "R_TYPE",
    "BREAK_TYPE"
};

InstructionMemory::InstructionMemory(char* file_name) {
    //Open hex file for reading
    std::ifstream is (file_name, std::ifstream::binary);
    if (is) {

        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        // Set file-pointer back to beginning
        is.seekg (0, is.beg);


        // Determines the number of instructions in program
        // 4-bytes per instruction, chop off extra bytes in case of error
        if(length%4 ==0){
            num_instructions=length/4;
        }else{
            std::cout<<"WARNING: Number of bytes not divisible by 4, chopping off the end to fix\n";
            num_instructions = (length-(length%4))/4;
        }

        // Create an array of empty decoded instructions the length of the file/4
        instruction_list = new DecodedInst[num_instructions];

        //Create a 32-bit buffer to hold a single instruction
        char * buffer = new char[4];
        unsigned int* buffer_int = new unsigned int[4];

        //Integer version of instruction in little-endian
        unsigned int current_instruction;
        for(int i=0; i<num_instructions;i++){
            current_instruction = 0;

            //Reads 4 bytes into buffer char array
            is.read(buffer,4);

            // Converts signed char into unsigned int
            // This could be optimized for readabilty I think it is a good choice
            for(int x=0; x<4;x++){
                buffer_int[x] = (unsigned char)buffer[x];
            }

            //Converts little-endian data from char array to unsigned integer
            // 31            24  23            16  15             8   7             0
            // [X X X X X X X X] [X X X X X X X X] [X X X X X X X X] [X X X X X X X X]
            //    buffer_int[0]     buffer_int[1]     buffer_int[2]    buffer_int[3]
            current_instruction = (buffer_int[0]<<24) + (buffer_int[1]<<16) + (buffer_int[2]<<8) + (buffer_int[3]);

            instruction_list[i] = DecodedInst(current_instruction);
        }
        //Buffers are no longer needed
        delete[] buffer;
        delete[] buffer_int;


        if (is){
            std::cout << "all characters read successfully.\n";
        }else{
            std::cout << "error: only " << is.gcount() << " could be read\n";
        }
        //Done with file
        is.close();
    }
}


//Returns a decoded_instruction from list at index
DecodedInst InstructionMemory::get_decoded_inst(unsigned int number){
    return instruction_list[number];
}



DecodedInst::DecodedInst(unsigned int instruction_in){
    my_type = BREAK_TYPE;
    rs1 = UNUSED_VAL;
    rs2 = UNUSED_VAL;
    rd = UNUSED_VAL;
    csr = UNUSED_VAL;
    opcode = UNUSED_VAL;
    imm = UNUSED_VAL;
    func7 = UNUSED_VAL;
    func3= UNUSED_VAL;
    instruction = instruction_in;

    process_inst();
}

DecodedInst::DecodedInst(){
    my_type = BREAK_TYPE;
    rs1 = UNUSED_VAL;
    rs2 = UNUSED_VAL;
    rd = UNUSED_VAL;
    csr = UNUSED_VAL;
    opcode = UNUSED_VAL;
    imm = UNUSED_VAL;
    func7 = UNUSED_VAL;
    func3= UNUSED_VAL;
    instruction = UNUSED_VAL;
}



void DecodedInst::print_info(){
    std::cout<<"\n--------------------------------------------\n";
    std::cout<<"Instruction: 0x"<<std::hex<<instruction<<std::endl;
    std::cout<<"Type: "<<type_words[my_type]<<std::endl;
    if (opcode != UNUSED_VAL) std::cout<<"Opcode: 0x"<<std::hex<<opcode<<std::endl;
    // if (imm != UNUSED_VAL) std::cout<<"Imm: 0x"<<std::hex<<imm<<std::endl;
    // Immediate can be -1 (=UNUSED_VAL) so the if statement is not useful here
    std::cout<<"Imm: 0x"<<std::hex<<imm<<std::endl;
    //if (imm != UNUSED_VAL) std::cout << "Imm = " << std::bitset<32>(imm)  << std::endl;
    if (rs1 != UNUSED_VAL) std::cout<<"rs1: 0x"<<std::hex<<rs1<<std::endl;
    if (rs2 != UNUSED_VAL) std::cout<<"rs2: 0x"<<std::hex<<rs2<<std::endl;
    if (rd != UNUSED_VAL) std::cout<<"rd: 0x"<<std::hex<<rd<<std::endl;
    if (csr != UNUSED_VAL) std::cout<<"csr: 0x"<<std::hex<<csr<<std::endl;
    if (func7 != UNUSED_VAL) std::cout<<"func7: 0x"<<std::hex<<func7<<std::endl;
    if (func3 != UNUSED_VAL) std::cout<<"func3: 0x"<<std::hex<<func3<<std::endl;
    std::cout<<"--------------------------------------------\n";
}


unsigned int DecodedInst::get_bits(int high_bit, int low_bit){
    unsigned int mask;
    mask = ((1 << (high_bit-low_bit+1)) - 1) << low_bit;

    //Used for debugging with #include <bitset>
    //std::cout << "data = " << std::bitset<32>(data)  << std::endl;
    //std::cout << "mask = " << std::bitset<32>(mask)  << std::endl;
    //std::cout << "eval = " << std::bitset<32>((data&mask)>>low_bit)  << std::endl;
    return (instruction & mask)>>low_bit;
}

signed int DecodedInst::sign_extend(signed int data, int data_lenght){
    int remaining_bits = 32 - data_lenght;
    int mask = pow(2, data_lenght) - 1;

    signed int sign_extended_data = (get_bits(31, 20) & mask) << remaining_bits;
    sign_extended_data >>= remaining_bits;

    return sign_extended_data;
}

bool DecodedInst::process_inst(unsigned int instruction_in){
    instruction = instruction_in;
    return process_inst();
}


bool DecodedInst::process_inst(){
    //Grab obcode from bit 6 downto 0
    opcode = get_bits(6,0);

    // F: Sign extend using intiger size property

    // Instruction Encoding depends on the instruction type.
    switch(opcode){
        case 0x33:
            // add, sub, slr, sll, xor, or, sra, and
            my_type = R_TYPE;
            func7 = get_bits(31, 25);
            rs2 = get_bits(24, 20);
            rs1 = get_bits(19,15);
            func3 = get_bits(14,12);
            rd = get_bits(11,7);
            break;
        case 0x03:
            // lb, lh, lw, lbu, lhu
            my_type = I_TYPE;
            imm = sign_extend(get_bits(31, 20), 12);
            rs1 = get_bits(19,15);
            func3 = get_bits(14,12);
            rd = get_bits(11, 7);
            break;
        case 0x13:
        {   // TODO: Added brackets here so I can initialise variables inside (make this for every case statement)
            // addi, slli, xori, srai, srai, srli, ori, andi
            my_type = I_TYPE;
            imm = sign_extend(get_bits(31, 20), 12);
            rs1 = get_bits(19,15);
            func3 = get_bits(14,12);
            rd = get_bits(11, 7);
            break;
        }
        case 0x23:
            //sb, sh, sw
            my_type = S_TYPE;
            // Double Check this logic
            imm = sign_extend((get_bits(31,25)<<5) + (get_bits(11,7)), 12);
            rs2=get_bits(24,20);
            rs1 = get_bits(19,15);
            func3= get_bits(14,12);
            break;
        case 0x63:
        {
            //beq, bne, blt, bge, bltu, bgeu
            my_type = B_TYPE;
            //Check this math, note, last bit is always 0
            int temp_imm = (get_bits(31,31)<<12)+(get_bits(7,7)<<11)+(get_bits(30,25)<<5)+(get_bits(11,8)<<1);
            imm = sign_extend(temp_imm, 13);
            rs2 = get_bits(24,20);
            rs1 = get_bits(19,15);
            func3 = get_bits(14,12);
            break;
        }
        case 0x37:
            //lui
            my_type = U_TYPE;
            imm = get_bits(31,12) << 12;    // F: bitshift added and tested
            rd = get_bits(11,7);
            break;
        case 0x67:
            //jalr
            my_type = I_TYPE;
            imm = sign_extend(get_bits(31, 20), 12);
            rs1 = get_bits(19,15);
            func3 = get_bits(14,12);
            rd = get_bits(11, 7);
            break;
        case 0x6F:
        {
            //jal
            my_type = J_TYPE;
            // Note bit 0 is always 0
            int temp_imm = (get_bits(31,31)<<20)+(get_bits(19,12)<<12)+(get_bits(20,20)<<11)+(get_bits(30,21)<<1);
            imm = sign_extend(temp_imm, 21);
            rd = get_bits(11,7);
            break;
        }
        case 0x17:
            //auipc
            my_type = U_TYPE;
            imm = get_bits(31,12) << 12;
            rd = get_bits(11,7);
            break;
        default:
            std::cout<<"Error Decoding, keep at break"<<std::endl;
            my_type = BREAK_TYPE;
    }
    return true;
}
