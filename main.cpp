#include "include/global.h"
#include "include/wrapper.h"
#include "include/IO.h"
#include "include/chip8.h"
#include "include/instructions.h"

int main(int argc, char** args)
{
    bool running = true;

    if(init(0) < 0)
    {
        std::cout << "Error initializing sdl 3" << std::endl;
        return 1;
    }

    Window window = Window("CHIP8 Emu", 64*20, 32*20, SDL_WINDOW_RESIZABLE);
    SDL_Surface*  surf = window.getChipSurface();
    CHIP_8 chip_8 = CHIP_8();

    chip_8.startCHIP();
    chip_8.load("roms/ibm.ch8");

    /*
    uint16_t testNum = 0x00E0;
    std::cout << testNum << std::endl;

    
    Instruction instr = createInstruction(testNum);

    std::cout << "first Nibble: " << (unsigned int)instr.firstNibble << std::endl;
    std::cout << "second Nibble: " << (unsigned int)instr.secondNibble << std::endl;
    std::cout << "third Nibble: " << (unsigned int)instr.thirdNibble << std::endl;
    std::cout << "fourth Nibble: " << (unsigned int)instr.fourthNibble << std::endl;

    std::cout << (unsigned int)getSecondByte(instr) << std::endl;
    std::cout << (unsigned int)getNibbles(instr) << std::endl;
    */

    SDL_Event event;

    while(running)
    {
        window.fill(0, 255, 0);
        fill(surf, 0, 0, 0);

        Uint64 start_time = SDL_GetPerformanceCounter();
        chip_8.run();

    

        // Get Events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }
        }

        if(running == false)
        {
            break;
        }

        // Update display
        window.drawFromDisplay(chip_8.display);

        updateWindow(window);

        Uint64 end_time = SDL_GetPerformanceCounter();

        float elapsed_time = (end_time-start_time) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;
        float delay = 16.6666f - elapsed_time;

        if(delay < 0)
        {
            delay = 0;
        }

        SDL_Delay(SDL_floor(delay));
    
    }

    destroy(window);

    quit();

    return 0;
}