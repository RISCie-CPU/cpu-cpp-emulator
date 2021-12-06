#include "register_file.hpp"

RegisterFile::RegisterFile()
{
    register_array[0].update(10);
    register_array[3].update(14);
}

void RegisterFile::Test(){
    for(int i=0; i<32; i++){
        std::cout<<"Reg "<<std::dec<<i<<std::hex<<": 0x"<<register_array[i].stored_value<<std::endl;
    }
}

void RegisterFile::write(Emulator::Types::BUSES_t &BUS_in,int rd){
    register_array[rd].update(BUS_in.WB);
}

void RegisterFile::read(Emulator::Types::BUSES_t &BUS_in,int rs1, int rs2){
    BUS_in.RF0_TO_TR0 = register_array[rs1].stored_value;
    BUS_in.RF1_TO_TR1 = register_array[rs2].stored_value;
}