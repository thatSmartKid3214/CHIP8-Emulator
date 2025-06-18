#include "../include/chip8.h"
#include "../include/IO.h"



void CHIP_8::startCHIP()
{
    // Load font
    for(int i = 0; i < FONTSIZE; i++)
    {
        memory[fontStart+i] = font[i];
    }

    running = true;
}


void CHIP_8::load(std::string file)
{
    uint8_t* rom = loadROM(file, romSize);

    for(int i = 0; i < romSize; i++)
    {
        memory[startAddress + i] = rom[i];
    }

    program_counter = 0x200;
    delay_timer = 0;

}

void CHIP_8::run()
{
    execute();
}

Instruction CHIP_8::fetch()
{
    uint16_t data;

    data = (memory[program_counter] << 8) | memory[program_counter+1];
    program_counter += 2;

    Instruction instr = createInstruction(data);
    return instr;
}

void CHIP_8::execute()
{

    Instruction instr = fetch();
    uint8_t secondByte = getSecondByte(instr);
    uint16_t nibbles = getNibbles(instr);

    switch(instr.firstNibble)
    {
        case 0x0:
            if( nibbles == 0x0E0) {
                clearDisplay(display);

                std::cout << "cleared!" << std::endl;

            }
            break;
        case 0x1:
            jumpAddr(program_counter, nibbles);

            std::cout << "Jumped to: " << nibbles << std::endl;

            break;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6:
            setRegister(registers, instr.secondNibble, secondByte);

            std::cout << "set register: " << (int)instr.secondNibble << " to " << (int)secondByte << std::endl;

            break;
        case 0x7:
            addRegister(registers, instr.secondNibble, secondByte);

            std::cout << "added " << (int)secondByte << " to register: " << (int)instr.secondNibble <<std::endl;

            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            setIndexRegister(index_register, nibbles);

            std::cout << "Set index register to: " << nibbles << std::endl;

            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD:
            draw(memory, registers, display, index_register, instr.secondNibble, instr.thirdNibble, instr.fourthNibble);

            std::cout << "Draw command!" << std::endl;

            break;
        case 0xE:
            break;
        case 0xF:
            break;
    }

}




