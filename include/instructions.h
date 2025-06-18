#ifndef INSTR_H
#define INSTR_H
#include "global.h"

struct Instruction
{
    uint8_t firstNibble;
    uint8_t secondNibble;
    uint8_t thirdNibble;
    uint8_t fourthNibble;
};

Instruction createInstruction(uint16_t data);

uint8_t getSecondByte(Instruction instr);
uint16_t getNibbles(Instruction instr);

// Instructions
void clearDisplay(bool* display);
void jumpAddr(uint16_t &pc, int location);
void setRegister(uint8_t* registers, int reg, int value);
void addRegister(uint8_t* registers, int reg, int value);
void setIndexRegister(uint16_t &index_reg, int value);
void draw(uint8_t* memory, uint8_t* registers, bool* display, int index_reg, int pos_x, int pos_y, int num_bytes);


#endif