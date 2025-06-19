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
        display[i] = 0;
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

void draw(uint8_t* memory, uint8_t* registers, bool* display , int index_reg, int pos_x, int pos_y, int num_bytes)
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
                display[position] = 0;
                registers[0xF] = 1;
            } else if ((pixel >> (7-i)) == 1 && display[position] == false)
            {
                display[position] = true;
            }
        }

        y++;
    }

}


void call(uint16_t* stack, uint16_t &pc, uint8_t &sp, int location)
{
    stack[sp] = pc;
    sp += 1;

    pc = location;
}

void ret(uint16_t* stack, uint16_t &pc, uint8_t &sp)
{
    sp -= 1;
    pc = stack[sp];
}

void skipEqual(uint8_t* registers, uint16_t &pc, int reg, int value)
{
    if(registers[reg] == value)
        pc += 2;
}

void skipNotEqual(uint8_t* registers, uint16_t &pc, int reg, int value)
{
    if(registers[reg] != value)
        pc += 2;
}

void skipRegEqual(uint8_t* registers, uint16_t &pc, int reg_x, int reg_y)
{
    if(registers[reg_x] == registers[reg_y])
        pc += 2;
}

void skipRegNotEqual(uint8_t* registers, uint16_t &pc, int reg_x, int reg_y)
{
    if(registers[reg_x] != registers[reg_y])
        pc += 2;
}

void set(uint8_t* registers, int reg_x, int reg_y)
{
    registers[reg_x] = registers[reg_y];
}

void OR(uint8_t* registers, int reg_x, int reg_y)
{
    registers[reg_x] = registers[reg_x] | registers[reg_y];
}

void AND(uint8_t* registers, int reg_x, int reg_y)
{
    registers[reg_x] = registers[reg_x] & registers[reg_y];
}

void XOR(uint8_t* registers, int reg_x, int reg_y)
{
    registers[reg_x] = registers[reg_x] ^ registers[reg_y];
}

void ADD(uint8_t* registers, int reg_x, int reg_y)
{
    unsigned int val = (unsigned int)registers[reg_x] + (unsigned int)registers[reg_y];
    if(val > 255)
    {
        registers[0xF] = 1;
    } else {
        registers[0xF] = 0;
    }

    registers[reg_x] = val;
}

void SUBTRACT(uint8_t* registers, int reg_x, int reg_y, int operation)
{
    if (operation == 0x5)
    {
        if(registers[reg_y] > registers[reg_x])
        {
            registers[0xF] = 0;
        } else {
            registers[0xF] = 1;
        }

        registers[reg_x] -= registers[reg_y];
    }

    if (operation == 0x7)
    {
        if(registers[reg_y] < registers[reg_x])
        {
            registers[0xF] = 0;
        } else {
            registers[0xF] = 1;
        }

        registers[reg_x] = registers[reg_y]-registers[reg_x];
    }
}


void offsetJump(uint8_t* registers, uint16_t &pc, int location)
{
    pc = location + registers[0x0];
}

void bitShiftLeft(uint8_t* registers, int reg_x, int reg_y)
{
    uint8_t bit = (registers[reg_x] & 128) >> 7;

    registers[reg_x] = registers[reg_x] << 1;

    registers[0xF] = bit;
}

void bitShiftRight(uint8_t* registers, int reg_x, int reg_y)
{
    uint8_t bit = registers[reg_x] & 1;
    registers[reg_x] = registers[reg_x] >> 1;

    registers[0xF] = bit;
}

void ifPressed(uint8_t* registers, bool* keys, uint16_t &pc, int reg)
{
    int vx = registers[reg];

    if(keys[vx])
    {
        pc += 2;
    }
}

void ifNotPressed(uint8_t* registers, bool* keys, uint16_t &pc, int reg)
{
    int vx = registers[reg];

    if(!keys[vx])
    {
        pc += 2;
    }
}

void getTimer(uint8_t* registers, int reg, uint8_t &timer)
{
    registers[reg] = timer;
}

void setDelayTimer(uint8_t* registers, int reg, uint8_t &timer)
{
    timer = registers[reg];
}

void store(uint8_t* memory, uint8_t* registers, uint16_t &index_reg, int reg)
{
    for(int i = 0; i <= reg; i++)
    {
        memory[index_reg + i] = registers[i];
    }

    //index_reg = index_reg + reg + 1;

}

void read(uint8_t* memory, uint8_t* registers, uint16_t &index_reg, int reg)
{

    std::cout << reg << std::endl;

    for(int i = 0; i <= reg; i++)
    {
        registers[i] = memory[index_reg + i];

        std::cout << (int)registers[i] << std::endl;
    }
    
    //index_reg = index_reg + reg + 1;
}


void BCDConversion(uint8_t* memory, uint8_t* registers, uint16_t index_reg, int reg)
{
    unsigned int value = registers[reg];
    int remainder = value%100;

    std::cout << value << std::endl;

    if(value-remainder < 100)
    {
        memory[index_reg] = 0;
        value = remainder;
        remainder = value%10;
        memory[index_reg+1] = (value-remainder)/10;
        memory[index_reg+2] = remainder;

        std::cout << 0 << "--" << (value-remainder)/10 << "--" << remainder <<  std::endl;

    } else {
        memory[index_reg] = (value-remainder)/100;

        std::cout << (value-remainder)/100 << "--";

        value = remainder;
        remainder = value%10;
        memory[index_reg+1] = (value-remainder)/10;
        memory[index_reg+2] = remainder;

        std::cout << (value-remainder)/10 << "--" << remainder <<  std::endl;
    }

}


void addToIndex(uint8_t* registers, uint16_t &index_reg, int reg)
{

    if((int)index_reg + registers[reg] > 0xFFF)
    {
        registers[0xF] = 1;
    }

    index_reg += registers[reg];
}



void waitForKey(uint8_t* registers, bool* keys, uint16_t &pc, uint8_t wr, int reg)
{
    int vx = registers[reg];
    bool wait = true;
    wr = reg;

    if(!keys[vx])
    {
        pc -= 2;
        return;
    }

    wait = false;
    pc += 2;
    std::cout << "Pressed!" << std::endl;
}


void getFont(uint8_t* registers, uint16_t &index_reg, int reg)
{
    int fontIndex = registers[reg];

    index_reg = fontStart + (fontIndex*5);
}

void random(uint8_t* registers, int reg, int value)
{
    uint8_t num = rand() % (value+1);

    num = num & value;

    registers[reg] = num;
}
