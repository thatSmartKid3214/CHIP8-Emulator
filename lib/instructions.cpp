#include "../include/instructions.h"


// Note: Have to figure out endianess, because the program works, but can break because it only assumes one endianess

Instruction createInstruction(uint16_t data)
{
    uint16_t mask = 15;
    Instruction instr;

    instr.fourthNibble = (data & mask) % 16;
    instr.thirdNibble = ((data & (mask << 4)) >> 4) % 16;
    instr.secondNibble = ((data & (mask << 8)) >> 8) % 16;
    instr.firstNibble = ((data & (mask << 12)) >> 12) % 16;

    return instr;
}

uint8_t getSecondByte(Instruction instr)
{
    return (instr.thirdNibble << 4) | instr.fourthNibble;
}


uint16_t getNibbles(Instruction instr)
{
    uint16_t nibbles = 0;

    nibbles = (instr.secondNibble << 8) | (instr.thirdNibble << 4) | instr.fourthNibble;

    return nibbles;
}

// Instructions
void clearDisplay(bool* display)
{
    for(int i = 0; i < WIDTH*HEIGHT; i++)
    {
        display[i] = false;
    }
}


void jumpAddr(uint16_t &pc, int location)
{
    pc = location;
}

void setRegister(uint8_t* registers, int reg, int value)
{
    registers[reg] = value;
}

void addRegister(uint8_t* registers, int reg, int value)
{
    registers[reg] += value;
}

void setIndexRegister(uint16_t &index_reg, int value)
{
    index_reg = value;
}

void draw(uint8_t* memory, uint8_t* registers, bool* display, int index_reg, int pos_x, int pos_y, int num_bytes)
{
    int x = registers[pos_x]%WIDTH;
    int y = registers[pos_y]%HEIGHT;
    registers[0xF] = 0;
    uint8_t mask = 128;

    for(unsigned int row = 0; row < num_bytes; ++row)
    {

        if(y >= HEIGHT)
        {
            break;
        }

        uint8_t byte = memory[index_reg+row];
        for(unsigned int i = 0; i < 8; ++i)
        {
            uint8_t pixel = byte & (mask >> i);
            int position = (y*WIDTH) + (x+i);

            if(x+i >= WIDTH)
            {
                break;
            }

            if ((pixel >> (7-i)) == 1 && display[position] == true)
            {
                display[position] = false;
                registers[0xF] = 1;
            } else if ((pixel >> (7-i)) == 1 && display[position] == false)
            {
                display[position] = true;
            }
        }

        y++;
    }

}


