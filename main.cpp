#include "include/global.h"
#include "include/wrapper.h"
#include "include/IO.h"
#include "include/chip8.h"
#include "include/instructions.h"

int main(int argc, char** args)
{
    bool running = true;
    srand(time(NULL));

    if(init(0) < 0)
    {
        std::cout << "Error initializing sdl 3" << std::endl;
        return 1;
    }

    Window window = Window("CHIP8 Emulator", 64*SCALE, 32*SCALE, SDL_WINDOW_RESIZABLE);
    CHIP_8 chip_8 = CHIP_8();

    chip_8.startCHIP();
    chip_8.load("roms/glitchGhost.ch8");

    SDL_Event event;

    float now = SDL_GetPerformanceCounter();
    float prev = 0;

    float accumalator = 0;

    while(running)
    {
        window.fill(0, 0, 0);

        now = SDL_GetPerformanceCounter();
        accumalator = now-prev;
        prev = now;
        chip_8.run();

        // Get Events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }

            if(event.type == SDL_EVENT_KEY_DOWN)
            {
                switch(event.key.key)
                {
                    case SDLK_1:
                        chip_8.keys[0x1] = 1;
                        break;
                    case SDLK_2:
                        chip_8.keys[0x2] = 1;
                        break;
                    case SDLK_3:
                        chip_8.keys[0x3] = 1;
                        break;
                    case SDLK_4:
                        chip_8.keys[0xC] = 1;
                        break;
                    case SDLK_Q:
                        chip_8.keys[0x4] = 1;
                        break;
                    case SDLK_W:
                        chip_8.keys[0x5] = 1;
                        break;
                    case SDLK_E:
                        chip_8.keys[0x6] = 1;
                        break;
                    case SDLK_R:
                        chip_8.keys[0xD] = 1;
                        break;
                    
                    case SDLK_A:
                        chip_8.keys[0x7] = 1;
                        break;
                    case SDLK_S:
                        chip_8.keys[0x8] = 1;

                        break;
                    case SDLK_D:
                        chip_8.keys[0x9] = 1;
                        break;
                    case SDLK_F:
                        chip_8.keys[0xE] = 1;
                        break;
                    
                    case SDLK_Z:
                        chip_8.keys[0xA] = 1;
                        break;
                    case SDLK_X:
                        chip_8.keys[0x0] = 1;
                        break;
                    case SDLK_C:
                        chip_8.keys[0xB] = 1;
                        break;
                    case SDLK_V:
                        chip_8.keys[0xF] = 1;
                        break;
                }
            }

            if(event.type == SDL_EVENT_KEY_UP)
            {
                switch(event.key.key)
                {
                    case SDLK_1:
                        chip_8.keys[0x1] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x1);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_2:
                        chip_8.keys[0x2] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x2);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_3:
                        chip_8.keys[0x3] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x3);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_4:
                        chip_8.keys[0xC] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xC);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;

                    case SDLK_Q:
                        chip_8.keys[0x4] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x4);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_W:
                        chip_8.keys[0x5] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x5);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_E:
                        chip_8.keys[0x6] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x6);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_R:
                        chip_8.keys[0xD] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xD);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    
                    case SDLK_A:
                        chip_8.keys[0x7] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x7);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_S:
                        chip_8.keys[0x8] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x8);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_D:
                        chip_8.keys[0x9] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x9);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_F:
                        chip_8.keys[0xE] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xE);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    
                    case SDLK_Z:
                        chip_8.keys[0xA] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xA);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_X:
                        chip_8.keys[0x0] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0x0);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_C:
                        chip_8.keys[0xB] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xB);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                    case SDLK_V:
                        chip_8.keys[0xF] = 0;

                        if(chip_8.wait)
                        {
                            setRegister(chip_8.registers, chip_8.waitingReg, 0xF);
                            chip_8.wait = false;
                            chip_8.program_counter += 2;
                        }

                        break;
                }
            }
        }

        if(running == false)
        {
            break;
        }

        window.drawFromDisplay(chip_8.display);
        window.updateWindow();

        Uint64 end_time = SDL_GetPerformanceCounter();

        float elapsed_time = (end_time-now) / static_cast<float>(SDL_GetPerformanceFrequency()) * 1000.0f;
        float delay = 16.6666f - elapsed_time;

        if((int)chip_8.delay_timer-1 >= 0 && accumalator > 1/60)
        {
            chip_8.delay_timer -= 1;
            accumalator = 0;
        }

        if(delay < 0)
        {
            delay = 0;
        }

        //SDL_Delay(SDL_floor(delay));
    
    }

    window.destroy();

    quit();

    return 0;
}