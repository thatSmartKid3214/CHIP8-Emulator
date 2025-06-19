#ifndef INSTR_H
#define INSTR_H
#include "global.h"
#include "wrapper.h"

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
void draw(uint8_t* memory, uint8_t* registers, bool* display , int index_reg, int pos_x, int pos_y, int num_bytes);
void call(uint16_t* stack, uint16_t &pc, uint8_t &sp, int location);
void ret(uint16_t* stack, uint16_t &pc, uint8_t &sp);
void skipEqual(uint8_t* registers, uint16_t &pc, int reg, int value);
void skipNotEqual(uint8_t* registers, uint16_t &pc, int reg, int value);
void skipRegEqual(uint8_t* registers, uint16_t &pc, int reg_x, int reg_y);
void skipRegNotEqual(uint8_t* registers, uint16_t &pc, int reg_x, int reg_y);
void set(uint8_t* registers, int reg_x, int reg_y);

void OR(uint8_t* registers, int reg_x, int reg_y);
void AND(uint8_t* registers, int reg_x, int reg_y);
void XOR(uint8_t* registers, int reg_x, int reg_y);
void ADD(uint8_t* registers, int reg_x, int reg_y);
void SUBTRACT(uint8_t* registers, int reg_x, int reg_y, int operation);

void offsetJump(uint8_t* registers, uint16_t &pc, int location);
void bitShiftLeft(uint8_t* registers, int reg_x, int reg_y);
void bitShiftRight(uint8_t* registers, int reg_x, int reg_y);

void ifPressed(uint8_t* registers, bool* keys, uint16_t &pc, int reg);
void ifNotPressed(uint8_t* registers, bool* keys, uint16_t &pc, int reg);
void waitForKey(uint8_t* registers, bool* keys, uint16_t &pc, uint8_t wr, int reg);

void getTimer(uint8_t* registers, int reg, uint8_t &timer);
void setDelayTimer(uint8_t* registers, int reg, uint8_t &timer);

void store(uint8_t* memory, uint8_t* registers, uint16_t &index_reg, int reg);
void read(uint8_t* memory, uint8_t* registers, uint16_t &index_reg, int reg);

void BCDConversion(uint8_t* memory, uint8_t* registers, uint16_t index_reg, int reg);

void addToIndex(uint8_t* registers, uint16_t &index_reg, int reg);
void getFont(uint8_t* registers, uint16_t &index_reg, int reg);

void random(uint8_t* registers, int reg, int value);

#endif