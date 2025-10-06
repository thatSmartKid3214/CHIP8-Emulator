#include "../include/chip8.h"
#include "../include/IO.h"



void CHIP_8::startCHIP()
{
    // Load font
    for(int i = 0; i < FONTSIZE; i++)
    {
        memory[fontStart+i] = font[i];
    }

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

    running = true;

    delete[] rom;

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

    if(!running && !stepped)
    {
        return;
    }

    Instruction instr = fetch();
    uint8_t secondByte = getSecondByte(instr);
    uint16_t nibbles = getNibbles(instr);

    switch(instr.firstNibble)
    {
        case 0x0:
            if( nibbles == 0x0E0) {
                clearDisplay(display);

                //std::cout << "cleared!" << std::endl;
            }

            if(nibbles == 0x0EE)
            {

                ret(stack, program_counter, stack_pointer);

                //std::cout << "return" << std::endl;
            }

            break;
        case 0x1:
            jumpAddr(program_counter, nibbles);

            //std::cout << "Jumped to: " << nibbles << std::endl;

            break;
        case 0x2:
            call(stack, program_counter, stack_pointer, nibbles);

            //std::cout << "Call subroutine at: " << nibbles << std::endl;

            break;
        case 0x3:
            skipEqual(registers, program_counter, instr.secondNibble, secondByte);

            //std::cout << "Skipped next insturction!" << std::endl;

            break;
        case 0x4:
            skipNotEqual(registers, program_counter, instr.secondNibble, secondByte);
            //std::cout << "Skipped next instruction because value was not equal!" << std::endl;
            break;
        case 0x5:
            skipRegEqual(registers, program_counter, instr.secondNibble, instr.thirdNibble);
            //std::cout << "Same value in registers: Skipping!" << std::endl;
            break;
        case 0x6:
            setRegister(registers, instr.secondNibble, secondByte);

            //std::cout << "set register: " << (int)instr.secondNibble << " to " << (int)secondByte << std::endl;

            break;
        case 0x7:
            addRegister(registers, instr.secondNibble, secondByte);

            //std::cout << "added " << (int)secondByte << " to register: " << (int)instr.secondNibble <<std::endl;

            break;
        case 0x8:
            //std::cout << "logic operation" << std::endl;
            switch(instr.fourthNibble)
            {

                case 0x0:
                    set(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0x1:
                    OR(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0x2:
                    AND(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0x3:
                    XOR(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0x4:
                    ADD(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0x5: case 0x7:
                    SUBTRACT(registers, instr.secondNibble, instr.thirdNibble, instr.fourthNibble);
                    break;
                case 0x6:
                    bitShiftRight(registers, instr.secondNibble, instr.thirdNibble);
                    break;
                case 0xE:
                    bitShiftLeft(registers, instr.secondNibble, instr.thirdNibble);
                    break;
            }

            break;
        case 0x9:
            skipRegNotEqual(registers, program_counter, instr.secondNibble, instr.thirdNibble);

            //std::cout << "Different values in registers: Skipping!" << std::endl;

            break;
        case 0xA:
            setIndexRegister(index_register, nibbles);

            //std::cout << "Set index register to: " << nibbles << std::endl;

            break;
        case 0xB:
            offsetJump(registers, program_counter, nibbles);
            break;
        case 0xC:
            random(registers, instr.secondNibble, secondByte);
            break;
        case 0xD:
            draw(memory, registers, display, index_register, instr.secondNibble, instr.thirdNibble, instr.fourthNibble);

            //std::cout << "Draw command!" << std::endl;

            break;
        case 0xE:

            switch(secondByte)
            {
                case 0x9E:
                    ifPressed(registers, keys, program_counter, instr.secondNibble);
                    break;
                case 0xA1:
                    ifNotPressed(registers, keys, program_counter, instr.secondNibble);
                    break;
            }
        
            break;
        case 0xF:
            switch(secondByte)
            {
                case 0x07:
                    //std::cout << "Storing value of DT in register: " << instr.secondNibble << std::endl;
                    getTimer(registers, instr.secondNibble, delay_timer);
                    break;
                case 0x15:
                    //std::cout << "Setting timer!" << std::endl;
                    setDelayTimer(registers, instr.secondNibble, delay_timer);
                    break;
                case 0x33:
                    //std::cout << "Converting!" << std::endl;
                    BCDConversion(memory, registers, index_register, instr.secondNibble);
                    break;
                case 0x1E:
                    addToIndex(registers, index_register, instr.secondNibble);
                    break;
                case 0x0A:

                    if(wait == false)
                    {
                        wait = true;
                        waitingReg = instr.secondNibble;
                    }

                    if(wait == true)
                    {
                        program_counter -= 2;
                        //std::cout << "Waiting!" << std::endl;
                    }

                    break;
                case 0x29:
                    getFont(registers, index_register, instr.secondNibble);
                    break;    
                case 0x55:
                    store(memory, registers, index_register, instr.secondNibble);

                    //std::cout << "store data!" << std::endl;

                    break;
                case 0x65:
                    read(memory, registers, index_register, instr.secondNibble);
                    
                    //std::cout << "read data!" << std::endl;
                    break;
            }

            break;
    }

    if(stepped == true) stepped = false;

}




