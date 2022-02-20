#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <cstdlib>
#include <iostream>
#include <bitset>

#include "types.hpp"
#include "consts.hpp"
#include "debug.hpp"
#include "instruction_memory.hpp"
#include "control_unit.hpp"
#include "program_counter.hpp"
#include "register.hpp"
#include "register_file.hpp"
#include "alu_sh.hpp"
#include "data_memory.hpp"


class Example : public olc::PixelGameEngine
{
public:
    Example(char *filename)
    {
        sAppName = "Example";
        Rom      = new InstructionMemory(filename);
    }

    char *current_filename;
    Emulator::Types::control_lines_t control_lines;
    Emulator::Types::BUSES_t BUS;
    // Rom has to be a pointer as it's value is not known when initialized
    InstructionMemory *Rom;
    ControlUnit Decoder;
    ProgramCounter Program_counter;
    Register TR0;
    Register TR1;
    Register TR2;
    ALU_SH ALU;
    RegisterFile Register_file;
    DataMemory Data_memory;

    int cur_scan_code;

    // Initialize basic variables
    int phase = 0; // either 0 or 1
    int clock = 0; // either 0 or 1

    bool running = true;
    // Not used by CPU, just for diagnostics
    int counter = 0;

    bool didDraw    = false;
    int noDrawCount = 0;

public:
    bool OnUserCreate() override
    {
        std::cout << "Before or after" << std::endl;
        // Initialize BUS lanes to 0 (More will be added)
        BUS.IMM_TO_PC = 0;
        BUS.PC_to_IM  = 0;
        return true;
    }

    void WriteToScreen(unsigned addr, int data)
    { }

    bool OnUserUpdate(float fElapsedTime) override
    {
        while (true)
        {
            // This will be set to true, if VRAM is wrtitten
            didDraw = false;


            // Collect Keyboard input
            if (IsFocused())
            {
                if (GetKey(olc::Key::A).bHeld)
                {
                    cur_scan_code = 0x1C;
                }
                else if (GetKey(olc::Key::B).bHeld)
                {
                    cur_scan_code = 0x32;
                }
                else if (GetKey(olc::Key::C).bHeld)
                {
                    cur_scan_code = 0x21;
                }
                else if (GetKey(olc::Key::D).bHeld)
                {
                    cur_scan_code = 0x23;
                }
                else if (GetKey(olc::Key::E).bHeld)
                {
                    cur_scan_code = 0x24;
                }
                else if (GetKey(olc::Key::F).bHeld)
                {
                    cur_scan_code = 0x2B;
                }
                else if (GetKey(olc::Key::G).bHeld)
                {
                    cur_scan_code = 0x34;
                }
                else if (GetKey(olc::Key::H).bHeld)
                {
                    cur_scan_code = 0x33;
                }
                else if (GetKey(olc::Key::I).bHeld)
                {
                    cur_scan_code = 0x43;
                }
                else if (GetKey(olc::Key::J).bHeld)
                {
                    cur_scan_code = 0x3B;
                }
                else if (GetKey(olc::Key::K).bHeld)
                {
                    cur_scan_code = 0x42;
                }
                else if (GetKey(olc::Key::L).bHeld)
                {
                    cur_scan_code = 0x4B;
                }
                else if (GetKey(olc::Key::M).bHeld)
                {
                    cur_scan_code = 0x3A;
                }
                else if (GetKey(olc::Key::N).bHeld)
                {
                    cur_scan_code = 0x31;
                }
                else if (GetKey(olc::Key::O).bHeld)
                {
                    cur_scan_code = 0x44;
                }
                else if (GetKey(olc::Key::P).bHeld)
                {
                    cur_scan_code = 0x4D;
                }
                else if (GetKey(olc::Key::Q).bHeld)
                {
                    cur_scan_code = 0x15;
                }
                else if (GetKey(olc::Key::R).bHeld)
                {
                    cur_scan_code = 0x2D;
                }
                else if (GetKey(olc::Key::S).bHeld)
                {
                    cur_scan_code = 0x1B;
                }
                else if (GetKey(olc::Key::T).bHeld)
                {
                    cur_scan_code = 0x2C;
                }
                else if (GetKey(olc::Key::U).bHeld)
                {
                    cur_scan_code = 0x3C;
                }
                else if (GetKey(olc::Key::V).bHeld)
                {
                    cur_scan_code = 0x2A;
                }
                else if (GetKey(olc::Key::W).bHeld)
                {
                    cur_scan_code = 0x1D;
                }
                else if (GetKey(olc::Key::X).bHeld)
                {
                    cur_scan_code = 0x22;
                }
                else if (GetKey(olc::Key::Y).bHeld)
                {
                    cur_scan_code = 0x1A;
                }
                else if (GetKey(olc::Key::Z).bHeld)
                {
                    cur_scan_code = 0x35;
                }
                else if (GetKey(olc::Key::ENTER).bHeld)
                {
                    cur_scan_code = 0x5A;
                }
                else if (GetKey(olc::Key::BACK).bHeld)
                {
                    cur_scan_code = 0x66;
                }
                else if (GetKey(olc::Key::SPACE).bHeld)
                {
                    cur_scan_code = 0x29;
                }
                else if (GetKey(olc::Key::K1).bHeld)
                {
                    cur_scan_code = 0x16;
                }
                else if (GetKey(olc::Key::K2).bHeld)
                {
                    cur_scan_code = 0x1E;
                }
                else if (GetKey(olc::Key::K3).bHeld)
                {
                    cur_scan_code = 0x26;
                }
                else if (GetKey(olc::Key::K4).bHeld)
                {
                    cur_scan_code = 0x25;
                }
                else if (GetKey(olc::Key::K5).bHeld)
                {
                    cur_scan_code = 0x2E;
                }
                else if (GetKey(olc::Key::K6).bHeld)
                {
                    cur_scan_code = 0x36;
                }
                else if (GetKey(olc::Key::K7).bHeld)
                {
                    cur_scan_code = 0x3D;
                }
                else if (GetKey(olc::Key::K8).bHeld)
                {
                    cur_scan_code = 0x3E;
                }
                else if (GetKey(olc::Key::K9).bHeld)
                {
                    cur_scan_code = 0x46;
                }
                else if (GetKey(olc::Key::K0).bHeld)
                {
                    cur_scan_code = 0x45;
                }
                else if (GetKey(olc::Key::UP).bHeld)
                {
                    cur_scan_code = 0xA9;
                }
                else if (GetKey(olc::Key::DOWN).bHeld)
                {
                    cur_scan_code = 0xAB;
                }
                else if (GetKey(olc::Key::LEFT).bHeld)
                {
                    cur_scan_code = 0xAA;
                }
                else if (GetKey(olc::Key::RIGHT).bHeld)
                {
                    cur_scan_code = 0xAC;
                }
                else if (GetKey(olc::Key::RETURN).bHeld)
                {
                    cur_scan_code = 0x5A;
                }
                else if (GetKey(olc::Key::ESCAPE).bHeld)
                {
                    cur_scan_code = 0x76;
                }
                else
                {
                    cur_scan_code = 0x0;
                }
            }

            // main loop
            // ---------------------------------------------------------------------------

            /*
             *  --------------- Phase 0 LOW ---------------
             *      RISCie will:
             *      1. Decode instructions into control signals
             *      2. Calculate immediate value
             *      3. Load data from register file
             */

            dbg("\n--------------- " << "New instruction (" << counter << ")" << " ---------------");
            // std::cout << "\n--------------- " << "New instruction (" << counter << ")" << " ---------------" << std::endl;

            // Get current instruction and print its properties
            DecodedInst current_inst = Rom->get_decoded_inst(BUS.PC_to_IM >> 2);
            // Decode current instruction into control lines and print them
            control_lines = Decoder.update_control_signals(current_inst.opcode, control_lines);


            #ifdef DEBUG
            current_inst.print_info();
            Decoder.print_control_signals(control_lines);
            #else
            # define dbg(MSG) do { } while (0)
            #endif

            control_lines.funct3 = current_inst.func3;
            control_lines.i      = (bool) (((current_inst.instruction) >> 30) & 1);

            // Send Immediate to Writeback if needed
            if (control_lines.IMM_TO_WB == 1) BUS.WB = current_inst.imm;
            // Immediate to Program counter
            BUS.IMM_TO_PC = current_inst.imm;

            Register_file.read(BUS, current_inst.rs1, current_inst.rs2);

            /*
             *  --------------- Phase 0 HIGH ---------------
             *      RISCie will:
             *      1. Store data to temporary registers
             *      (TR0 & TR1 will have data from register file)
             *      2. Waits until ALU will calculate its result
             */

            BUS = Program_counter.update_BUS(BUS, control_lines, 0, 1);

            // Store register output to temporary register 0 and 1
            BUS.TR0_TO_ALU0 = TR0.update(BUS.RF0_TO_TR0);
            BUS.TR1_TO_RAMD = TR1.update(BUS.RF1_TO_TR1);
            // Update temporary register 2
            BUS.TR2_TO_MUX = TR2.update(BUS.PC_TO_TR2);

            dbg("TR0: 0x" << std::hex << BUS.TR0_TO_ALU0);
            dbg("TR1: 0x" << std::hex << BUS.TR1_TO_RAMD);
            dbg("TR2: 0x" << std::hex << BUS.TR2_TO_MUX);

            // MUX (TR1 / Immediate) to ALU source 1. Depends on ALU_SRC
            if (control_lines.ALU_SRC == 0) BUS.ALU_MUX_TO_ALU1 = BUS.TR1_TO_RAMD;
            else BUS.ALU_MUX_TO_ALU1 = current_inst.imm;

            ALU.update(&BUS, control_lines);
            dbg("ALU output: 0x" << std::hex << BUS.ALU_TO_DM);
            // std::cout << "ALU output: 0x" << std::hex << BUS.ALU_TO_DM << std::endl;

            // Send ALU output to Writeback if needed
            if (control_lines.ALU_TO_WB == 1) BUS.WB = BUS.ALU_TO_DM;

            /*
             *  --------------- Phase 1 LOW ---------------
             *      RISCie will:
             *      Chill, waits till values from ALU are stable
             */

            // nothing important

            /*
             *  --------------- Phase 1 HIGH ---------------
             *      RISCie will:
             *      1. Store to RF/RAM/PC
             */
            // Store or load from Data memory
            if (control_lines.STR_TO_RAM == 1)
            {
                if (BUS.ALU_TO_DM >> 30 == 1)
                {
                    unsigned addr = BUS.ALU_TO_DM % 131072;
                    unsigned data = BUS.TR1_TO_RAMD;

                    int ypos = (int) (addr / 512);
                    int xpos = addr % 512;

                    int r_clr = 0;
                    int g_clr = 0;
                    int b_clr = 0;

                    int step = 1;

                    if (control_lines.funct3 == 0b000)
                    {
                        // Byte
                        // Not really nescessary:
                        // step = 1;
                    }
                    else if (control_lines.funct3 == 0b001)
                    {
                        // Half
                        step = 2;
                    }
                    else if (control_lines.funct3 == 0b010)
                    {
                        // word
                        step = 4;
                    }

                    for (int i = 0; i < step; i++)
                    {
                        r_clr = (data & (0b11100000 << (i * 8))) >> 5 + (i * 8);
                        g_clr = (data & (0b00011100 << (i * 8))) >> 2 + (i * 8);
                        b_clr = (data & (0b00000011 << (i * 8))) >> 0 + (i * 8);

                        Draw(xpos + i, ypos, olc::Pixel(r_clr * 36, g_clr * 36, b_clr * 85));
                    }

                    didDraw = true;
                }
                else
                {
                    // All other memory
                    Data_memory.store(&control_lines, &BUS);
                }
            }
            else if (control_lines.RAM_TO_WB == 1)
            {
                // On load first check if it is reading from the keyboard port
                // This is being done in main() as the olcPixelGameEngine fucntions are located here
                if (BUS.ALU_TO_DM == 0x80000004)
                {
                    BUS.WB = cur_scan_code;
                }
                else
                {
                    Data_memory.load(&control_lines, &BUS);
                }
            }

            // MUX (WB / TR2) as data to destination register. Depends on PC_SRC 0 or 1
            if ((control_lines.PC_SRC_0 | control_lines.PC_SRC_1) == 0) BUS.WB_TO_RF = BUS.WB;
            else BUS.WB_TO_RF = BUS.PC_TO_TR2;

            // Store to register file in needed
            if (control_lines.STR_TO_RF == 1) Register_file.write(BUS, current_inst.rd);

            // DEBUG:
            // Register_file.Test();

            // Store to program counter + load new value (loading new value is done @ falling edge)
            BUS = Program_counter.update_BUS(BUS, control_lines, 1, 0);

            // For debug only
            counter++;

            // if (counter == 33)
            // {
            //     exit(3);
            //     return true;
            // }

            // std::cout<<noDrawCount<<std::endl;
            if (didDraw == false)
            {
                noDrawCount++;
                if (noDrawCount > 500000)
                {
                    didDraw = true;
                    // std::cout<<"Did Draw = true"<<rand() % 100<<std::endl;
                    noDrawCount = 0;
                }
            }
            else
            {
                noDrawCount = 0;
            }
            // --------------------------------------------------------------------------------------------
            // End Loop

            if (didDraw == true)
            {
                break;
            }
        }
        return true;
    } // OnUserUpdate
};

int main(int argc, char *argv[])
{
    Example demo(argv[1]);
    // Screen Size of 320x240 pixels with each pixel representing 2x2 screen pixels
    if (demo.Construct(320, 240, 3, 3))
        demo.Start();

    return 0;
} // main
