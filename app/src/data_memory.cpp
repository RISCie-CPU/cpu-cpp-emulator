#include "data_memory.hpp"

void DataMemory::print(){
    for (int i = 0; i < 40*4; i+=4){
        std::cout << i << "[" << (int)ram[i+3] << (int)ram[i+2] << (int)ram[i+1] << (int)ram[i]  << "] ";

    }
    std::cout << "\n";
}


DataMemory::DataMemory(){
    ram = new uint8_t[131072 * 4];
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
            addr = addr % 524288;  // 2 ** 19
            output = sign_extend(ram[addr], 8);
            std::cout << "Data memory: lb, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")" << std::endl;
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
            addr = addr % 524288;  // 2 ** 19
            output = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            output = sign_extend(output, 16);
            std::cout << "Data memory: lh, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")" << std::endl;
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
            output = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            output |= ram[addr + 2] << 16;
            output |= ram[addr + 3] << 24;
            std::cout << "Data memory: lw, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")" << std::endl;
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
            addr = addr % 524288;  // 2 ** 19
            output = sign_extend(ram[addr], 8);
            std::cout << "Data memory: lbu, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")" << std::endl;
        }
        // VRAM

        // Special registers
        // Special registers
        if (addr >> 30 != 0)
        {
            output = 0;
        }
    }
    // By halfes unsigned (lhu):
    if (funct3 == 0b101)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            addr = addr % 524288;  // 2 ** 19
            output = ram[addr + 0];
            output |= ram[addr + 1] << 8;
            std::cout << "Data memory: lhu, 0x" << std::hex << output << " to WB (from: 0x" << std::hex << addr << ")" << std::endl;
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
}

void DataMemory::store(Emulator::Types::control_lines_t *control_lines_in, Emulator::Types::BUSES_t *BUS_in)
{
    int to_store = (*BUS_in).TR1_TO_RAMD;
    int addr = (*BUS_in).ALU_TO_DM;
    unsigned int funct3 = (*control_lines_in).funct3;

    // if (to_store == 0x700fe9c){
    //     exit(EXIT_FAILURE);
    // }

    // std::cout << "Addr: 0x" << std::hex << addr << std::endl;
    // std::cout << "Storing: 0x" << std::hex << to_store << std::endl;
    // std::cout << "ram[0x7fe88]: 0x" << std::hex << (int)ram[0x7fe88] << std::endl;

    // By bytes (sb):
    if (funct3 == 0b000)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            std::cout << "Data memory: sb, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]" << std::endl;
            addr = addr % 524288;  // 2 ** 19
            ram[addr] = to_store & 0xff;
        }
        // VRAM

        // Special registers
    }
    // By halfs (sh):
    if (funct3 == 0b001)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            std::cout << "Data memory: sh, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]" << std::endl;
            addr = addr % 524288;  // 2 ** 19
            ram[addr + 0] = (to_store & 0x00ff) >> 0;
            ram[addr + 1] = (to_store & 0xff00) >> 8;
        }
        // VRAM

        // Special registers
    }
    // By words (sw):
    if (funct3 == 0b010)
    {
        // SRAM
        if (addr >> 30 == 0)
        {
            std::cout << "Data memory: sw, 0x" << std::hex << to_store << " --> [0x" << std::hex << addr << "]" << std::endl;
            addr = addr % 524288;  // 2 ** 19
            ram[addr + 0] = (to_store & 0x000000ff) >> 0;
            ram[addr + 1] = (to_store & 0x0000ff00) >> 8;
            ram[addr + 2] = (to_store & 0x00ff0000) >> 16;
            ram[addr + 3] = (to_store & 0xff000000) >> 24;
        }
        // VRAM

        // Special registers
    }
}



// from block import Block
// from PIL import Image
// from data import Data
// import numpy as np
// import base64
// import numpy
// import io


// class DataMemory(Block):
//     def __init__(self, data: Data, socketio) -> None:

//         self.__socketio = socketio
//         super().__init__(data)

//         self.RAM = numpy.zeros(2 ** 19, dtype=numpy.uint8)
//         self.VRAM = numpy.zeros(2 ** 13, dtype=numpy.uint8)
//         self.last_time = 0

//     def clock_up(self):
//         self.load()
//         self.store()

//     def clock_down(self):
//         self.load()

//     def asynchronous(self):
//         # TODO VRAM -> property + setter
//         # current = time.time()

//         # if current - self.last_time > 0.1:
//         #     self.last_time = current

//         # Reverse the bit ordering
//         binary = np.unpackbits(self.VRAM).reshape(-1, 8)[:, ::-1] * 255

//         reshaped = np.reshape(binary, (256, 256))
//         cropped = np.array(reshaped[0:150, 0:200])

//         im = Image.fromarray(cropped.astype("uint8"))
//         raw_bytes = io.BytesIO()
//         im.save(raw_bytes, "BMP")
//         raw_bytes.seek(0)  # return to the start of the file
//         self.__socketio.emit("vga",
//                              {"image": f"data:image/bmp;base64,{base64.b64encode(raw_bytes.read()).decode('utf-8')}"},
//                              namespace="/pineapple")

//     def update_vga(self):
//         self.asynchronous()
//         # p = Process(target=self.asynchronous)
//         # p.start()

//     def store(self):
//         input_data = self.data.read_register_2
//         input_address = self.data.alu_out

//         prepared_instruction = bin(self.data.instruction)[2:].zfill(32)
//         funct3 = int(prepared_instruction[17:20], 2)

//         if self.data.MEM_STORE:
//             bin_address = bin(input_address)[2:].zfill(32)

//             # ukládání po bytech (b)
//             if funct3 == 0b000:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # print(f"Write B to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr] = input_data & 0xff
//                     self.update_vga()
//                     print(f"Write B to VRAM ({addr}) --> {input_data}, {hex(input_address)}, {input_data}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr] = input_data & 0xff

//             # ukládání po půlslovech (hw)
//             elif funct3 == 0b001:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % (16)
//                     print(f"Write HW to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr + 0] = (input_data & 0x00ff) >> 0
//                     self.VRAM[addr + 1] = (input_data & 0xff00) >> 8
//                     self.update_vga()
//                     print(f"Write HW to VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr + 0] = (input_data & 0x00ff) >> 0
//                     self.RAM[addr + 1] = (input_data & 0xff00) >> 8

//             # ukládání po slovech (w)
//             elif funct3 == 0b010:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % (16)
//                     print(f"Write W to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr + 0] = (input_data & 0x000000ff) >> 0
//                     self.VRAM[addr + 1] = (input_data & 0x0000ff00) >> 8
//                     self.VRAM[addr + 2] = (input_data & 0x00ff0000) >> 16
//                     self.VRAM[addr + 3] = (input_data & 0xff000000) >> 24
//                     self.update_vga()
//                     # print(f"Write W to VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr + 0] = (input_data & 0x000000ff) >> 0
//                     self.RAM[addr + 1] = (input_data & 0x0000ff00) >> 8
//                     self.RAM[addr + 2] = (input_data & 0x00ff0000) >> 16
//                     self.RAM[addr + 3] = (input_data & 0xff000000) >> 24

//     def load(self):
//         if self.data.MEM_LOAD:

//             input_data = self.data.read_register_2
//             input_address = self.data.alu_out

//             prepared_instruction = bin(self.data.instruction)[2:].zfill(32)
//             funct3 = int(prepared_instruction[17:20], 2)
//             bin_address = bin(input_address)[2:].zfill(32)
//             prepared_data = 0b00000000000000000000000000000000

//             # load byte (lb)
//             if funct3 == 0b000:

//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read B from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     sign_bit = (self.VRAM[addr] & 0x80) >> 7
//                     prepared_data = int(str(sign_bit) * 24, 2) << 8 | self.VRAM[addr]

//                     print(f"Read B from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     sign_bit = (self.RAM[addr] & 0x80) >> 7
//                     prepared_data = int(str(sign_bit) * 24, 2) << 8 | self.RAM[addr]

//             # load half (lh)
//             elif funct3 == 0b001:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read HW from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     sign_bit = (self.VRAM[addr] & 0x80) >> 7
//                     prepared_data |= self.VRAM[addr + 0]
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     prepared_data |= int(str(sign_bit) * 16, 2) << 16
//                     print(f"Read HW from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     # addr = input_address % 524288  # 2 ** 19
//                     addr = input_address

//                     sign_bit = (self.RAM[addr] & 0x80) >> 7
//                     prepared_data |= self.RAM[addr + 0]
//                     prepared_data |= self.RAM[addr + 1] << 8
//                     prepared_data |= int(str(sign_bit) * 16, 2) << 16

//             # load word (lw)
//             elif funct3 == 0b010:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read W from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data |= self.VRAM[addr + 0] << 0
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     prepared_data |= self.VRAM[addr + 2] << 16
//                     prepared_data |= self.VRAM[addr + 3] << 24
//                     # print(f"Read W from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     prepared_data |= self.RAM[addr + 0] << 0
//                     prepared_data |= self.RAM[addr + 1] << 8
//                     prepared_data |= self.RAM[addr + 2] << 16
//                     prepared_data |= self.RAM[addr + 3] << 24

//                     # load byte unsigned (lbu)
//             elif funct3 == 0b100:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     # print(f"Read lbu from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data = self.VRAM[addr]
//                     # print(f"Read lbu from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     prepared_data = self.RAM[input_address]

//             # load half unsigned (lhu)
//             elif funct3 == 0b101:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read lbu from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data = self.VRAM[addr]
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     print(f"Read lbu from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     prepared_data = self.RAM[addr]
//                     prepared_data |= self.RAM[addr + 1] << 8

//             # print(f"Load: {bin(prepared_data)}")
//             self.data.ram_out = prepared_data

// # if __name__ == '__main__':
// #     data = Data()
// #     ram = DataMemory(data, logger)
// #
// #     f3 = 0b001
// #     data.instruction = (f3 << 12)
// #
// #     data.MEM_STORE = 1
// #     data.MEM_LOAD = 0
// #
// #     # address:
// #     data.alu_out = 0xffffffff & 4
// #     # data:
// #     data.read_register_2 = 0xffffffff & 0b00000011_10000010
// #
// #     ram.clock_up()
// #     print(f"Storing: ram[{data.alu_out}]= {ram.RAM[4]}")
// #
// #     f3 = 0b100
// #     data.instruction = (f3 << 12)
// #
// #     data.MEM_STORE = 0
// #     data.MEM_LOAD = 1
// #
// #     ram.clock_down()
// #     # print(f"Loading: ram[{data.alu_out}]= {ram.RAM[4]}; word = {ram.RAM[data.alu_out]},{ram.RAM[data.alu_out+1]},{ram.RAM[data.alu_out+2]},{ram.RAM[data.alu_out+3]}")









// from block import Block
// from PIL import Image
// from data import Data
// import numpy as np
// import base64
// import numpy
// import io


// class DataMemory(Block):
//     def __init__(self, data: Data, socketio) -> None:

//         self.__socketio = socketio
//         super().__init__(data)

//         self.RAM = numpy.zeros(2 ** 19, dtype=numpy.uint8)
//         self.VRAM = numpy.zeros(2 ** 13, dtype=numpy.uint8)
//         self.last_time = 0

//     def clock_up(self):
//         self.load()
//         self.store()

//     def clock_down(self):
//         self.load()

//     def asynchronous(self):
//         # TODO VRAM -> property + setter
//         # current = time.time()

//         # if current - self.last_time > 0.1:
//         #     self.last_time = current

//         # Reverse the bit ordering
//         binary = np.unpackbits(self.VRAM).reshape(-1, 8)[:, ::-1] * 255

//         reshaped = np.reshape(binary, (256, 256))
//         cropped = np.array(reshaped[0:150, 0:200])

//         im = Image.fromarray(cropped.astype("uint8"))
//         raw_bytes = io.BytesIO()
//         im.save(raw_bytes, "BMP")
//         raw_bytes.seek(0)  # return to the start of the file
//         self.__socketio.emit("vga",
//                              {"image": f"data:image/bmp;base64,{base64.b64encode(raw_bytes.read()).decode('utf-8')}"},
//                              namespace="/pineapple")

//     def update_vga(self):
//         self.asynchronous()
//         # p = Process(target=self.asynchronous)
//         # p.start()

//     def store(self):
//         input_data = self.data.read_register_2
//         input_address = self.data.alu_out

//         prepared_instruction = bin(self.data.instruction)[2:].zfill(32)
//         funct3 = int(prepared_instruction[17:20], 2)

//         if self.data.MEM_STORE:
//             bin_address = bin(input_address)[2:].zfill(32)

//             # ukládání po bytech (b)
//             if funct3 == 0b000:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # print(f"Write B to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr] = input_data & 0xff
//                     self.update_vga()
//                     print(f"Write B to VRAM ({addr}) --> {input_data}, {hex(input_address)}, {input_data}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr] = input_data & 0xff

//             # ukládání po půlslovech (hw)
//             elif funct3 == 0b001:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % (16)
//                     print(f"Write HW to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr + 0] = (input_data & 0x00ff) >> 0
//                     self.VRAM[addr + 1] = (input_data & 0xff00) >> 8
//                     self.update_vga()
//                     print(f"Write HW to VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr + 0] = (input_data & 0x00ff) >> 0
//                     self.RAM[addr + 1] = (input_data & 0xff00) >> 8

//             # ukládání po slovech (w)
//             elif funct3 == 0b010:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % (16)
//                     print(f"Write W to SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     self.VRAM[addr + 0] = (input_data & 0x000000ff) >> 0
//                     self.VRAM[addr + 1] = (input_data & 0x0000ff00) >> 8
//                     self.VRAM[addr + 2] = (input_data & 0x00ff0000) >> 16
//                     self.VRAM[addr + 3] = (input_data & 0xff000000) >> 24
//                     self.update_vga()
//                     # print(f"Write W to VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     self.RAM[addr + 0] = (input_data & 0x000000ff) >> 0
//                     self.RAM[addr + 1] = (input_data & 0x0000ff00) >> 8
//                     self.RAM[addr + 2] = (input_data & 0x00ff0000) >> 16
//                     self.RAM[addr + 3] = (input_data & 0xff000000) >> 24

//     def load(self):
//         if self.data.MEM_LOAD:

//             input_data = self.data.read_register_2
//             input_address = self.data.alu_out

//             prepared_instruction = bin(self.data.instruction)[2:].zfill(32)
//             funct3 = int(prepared_instruction[17:20], 2)
//             bin_address = bin(input_address)[2:].zfill(32)
//             prepared_data = 0b00000000000000000000000000000000

//             # load byte (lb)
//             if funct3 == 0b000:

//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read B from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     sign_bit = (self.VRAM[addr] & 0x80) >> 7
//                     prepared_data = int(str(sign_bit) * 24, 2) << 8 | self.VRAM[addr]

//                     print(f"Read B from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     sign_bit = (self.RAM[addr] & 0x80) >> 7
//                     prepared_data = int(str(sign_bit) * 24, 2) << 8 | self.RAM[addr]

//             # load half (lh)
//             elif funct3 == 0b001:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read HW from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     sign_bit = (self.VRAM[addr] & 0x80) >> 7
//                     prepared_data |= self.VRAM[addr + 0]
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     prepared_data |= int(str(sign_bit) * 16, 2) << 16
//                     print(f"Read HW from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     # addr = input_address % 524288  # 2 ** 19
//                     addr = input_address

//                     sign_bit = (self.RAM[addr] & 0x80) >> 7
//                     prepared_data |= self.RAM[addr + 0]
//                     prepared_data |= self.RAM[addr + 1] << 8
//                     prepared_data |= int(str(sign_bit) * 16, 2) << 16

//             # load word (lw)
//             elif funct3 == 0b010:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read W from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data |= self.VRAM[addr + 0] << 0
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     prepared_data |= self.VRAM[addr + 2] << 16
//                     prepared_data |= self.VRAM[addr + 3] << 24
//                     # print(f"Read W from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     prepared_data |= self.RAM[addr + 0] << 0
//                     prepared_data |= self.RAM[addr + 1] << 8
//                     prepared_data |= self.RAM[addr + 2] << 16
//                     prepared_data |= self.RAM[addr + 3] << 24

//                     # load byte unsigned (lbu)
//             elif funct3 == 0b100:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     # print(f"Read lbu from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data = self.VRAM[addr]
//                     # print(f"Read lbu from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     prepared_data = self.RAM[input_address]

//             # load half unsigned (lhu)
//             elif funct3 == 0b101:
//                 # special registers
//                 if bin_address[0] == "1":
//                     addr = input_address % 16
//                     # addr = input_address - 0x80000000
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     prepared_data = 0
//                     #  !!!!!!!!!!!! Load 0 every time !!!!!!!!!!!!!!!!
//                     print(f"Read lbu from SP ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # VRAM
//                 elif bin_address[1] == "1":
//                     addr = input_address % 8192  # 2 ** 13
//                     # addr = input_address - 0x40000000
//                     prepared_data = self.VRAM[addr]
//                     prepared_data |= self.VRAM[addr + 1] << 8
//                     print(f"Read lbu from VRAM ({addr}) --> {input_data}, pulse count: {self.data.pulse_count}")
//                 # SRAM
//                 else:
//                     addr = input_address % 524288  # 2 ** 19
//                     # addr = input_address
//                     prepared_data = self.RAM[addr]
//                     prepared_data |= self.RAM[addr + 1] << 8

//             # print(f"Load: {bin(prepared_data)}")
//             self.data.ram_out = prepared_data

// # if __name__ == '__main__':
// #     data = Data()
// #     ram = DataMemory(data, logger)
// #
// #     f3 = 0b001
// #     data.instruction = (f3 << 12)
// #
// #     data.MEM_STORE = 1
// #     data.MEM_LOAD = 0
// #
// #     # address:
// #     data.alu_out = 0xffffffff & 4
// #     # data:
// #     data.read_register_2 = 0xffffffff & 0b00000011_10000010
// #
// #     ram.clock_up()
// #     print(f"Storing: ram[{data.alu_out}]= {ram.RAM[4]}")
// #
// #     f3 = 0b100
// #     data.instruction = (f3 << 12)
// #
// #     data.MEM_STORE = 0
// #     data.MEM_LOAD = 1
// #
// #     ram.clock_down()
// #     # print(f"Loading: ram[{data.alu_out}]= {ram.RAM[4]}; word = {ram.RAM[data.alu_out]},{ram.RAM[data.alu_out+1]},{ram.RAM[data.alu_out+2]},{ram.RAM[data.alu_out+3]}")