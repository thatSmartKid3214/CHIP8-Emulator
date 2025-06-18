#ifndef WRAPPER_H
#define WRAPPER_H

#include "global.h"

int init(SDL_InitFlags flags);
void quit();

class Window
{
    private:
        SDL_Window* win = NULL;
        SDL_Surface* surf = NULL;
        SDL_Surface* chipSurf = SDL_CreateSurface(WIDTH, HEIGHT, SDL_PIXELFORMAT_RGBA32);

    public:
        SDL_Rect screen_rect;

        Window(std::string title, int width, int height, SDL_WindowFlags flags);
        SDL_Window* getWindow();
        SDL_Surface* getSurface();
        SDL_Surface* getChipSurface();

        void fill(int r, int g, int b);
        void drawFromDisplay(bool* display);
};

void updateWindow(Window win);
void destroy(Window win);

void fill(SDL_Surface* surf, int r, int g, int b);

void setPixel(SDL_Surface* surf, int x, int y, int r, int g, int b);
Uint32 getPixel(SDL_Surface* surf, int x, int y);

#endif