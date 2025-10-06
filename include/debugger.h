#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "global.h"
#include "chip8.h"

class Debugger
{
    private:
        SDL_Texture* surface;
        TTF_Font* font;
        CHIP_8* chip_8;
        SDL_Renderer* renderer;

    public:
        Debugger(SDL_Renderer* renderer, TTF_Font* font, CHIP_8* chip_8, int width, int height);

        void togglePause();
        void stepThrough(bool next);
        void setBreakPoint(int location);
        void resetROM();
        void setProgramCounter(int pc);
        
        SDL_Texture* getSurface();
        void draw();
};

#endif



