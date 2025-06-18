#ifndef CHIP8_H
#define CHIP8_H

#include "global.h"
#include "instructions.h"

class CHIP_8 {

	private:
		Instruction fetch(); // The instruction gets fetched and decoded here.
		void execute(); 

    public:
        uint8_t memory[4096] = {};
        bool display[WIDTH*HEIGHT] = {false};
        uint16_t program_counter;
        uint16_t index_register;
        uint8_t registers[16];
        uint16_t stack[16];
        Uint8* stack_pointer = reinterpret_cast<Uint8*>(stack);
		uint8_t delay_timer; // Decreases at a rate of 60 Hz (60 times per second)

		int tick_rate = 60;

        int romSize;
		bool running = false;

        void startCHIP();
        void load(std::string file);

        void run();
};

#endif