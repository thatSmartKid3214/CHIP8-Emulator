#include "../include/debugger.h"



Debugger::Debugger(SDL_Renderer* renderer, TTF_Font* font, CHIP_8* chip_8, int width, int height)
{
    this->chip_8 = chip_8;
    this->font = font;
    this->renderer = renderer;

    surface = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_Texture* temp = SDL_GetRenderTarget(renderer);

}

void Debugger::togglePause()
{
    chip_8->running = !chip_8->running;
}

void Debugger::stepThrough(bool next)
{
    if(next == true) // Step to the next instruction
    {
        chip_8->program_counter += 2;
    } else {
        chip_8->program_counter -= 4;

        if(chip_8->program_counter < startAddress)
            chip_8->program_counter = startAddress;
    }

    chip_8->stepped = true;
} 

SDL_Texture* Debugger::getSurface()
{
    return surface;
}

void Debugger::setBreakPoint(int location)
{

}

void Debugger::resetROM()
{
    chip_8->program_counter = startAddress;
    clearDisplay(chip_8->display);
    chip_8->running = true;
}

void Debugger::setProgramCounter(int pc)
{
    
}

void Debugger::draw()
{
    SDL_SetRenderTarget(renderer, surface);
    SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);
    SDL_RenderClear(renderer);
}


