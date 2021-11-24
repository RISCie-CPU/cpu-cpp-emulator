#ifndef PINE_EMU_IM_H
#define PINE_EMU_IM_H

#define UNUSED_VAL 4294967295

enum inst_type {U_TYPE, J_TYPE, I_TYPE, B_TYPE, S_TYPE, R_TYPE,BREAK_TYPE};


class DecodedInst{
    public:

        // Initilizes all values to Maximum unsigned int, meaning NULL
        // Also calls process_inst()
        DecodedInst(unsigned int instruction_in);
        // Initilizes all values to Maximum unsigned int, meaning Null
        DecodedInst();
        // Used for testing only, prints all values
        void print_info();

        unsigned int instruction;
        inst_type my_type;
        unsigned int rs1;
        unsigned int rs2;
        unsigned int rd;
        unsigned int csr;
        unsigned int opcode;
        unsigned int imm;
        unsigned int func7;
        unsigned int func3;
    private: 
        // Numbered as 31,30,29,...,2,1,0
        // Returns an integer found by reading high_bit downto low_bit
        unsigned int get_bits(int high_bit, int low_bit);

        // Assigns all values based on instruction data and accepts instruction
        bool process_inst(unsigned int instruction_in);

        // Assigns all values based on aleady set instruction
        bool process_inst();
};


class InstructionMemory {
    private:
        DecodedInst* instruction_list;         
    public:
        InstructionMemory(char* file_name);
        unsigned int num_instructions;
        DecodedInst get_decoded_inst(unsigned int number);
};


#endif