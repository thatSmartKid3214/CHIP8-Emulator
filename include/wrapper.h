#ifndef WRAPPER_H
#define WRAPPER_H

#include "global.h"

int init(SDL_InitFlags flags);
void quit();

class Window
{
    private:
        SDL_Window* win = NULL;
        SDL_Renderer* renderer = NULL;

        SDL_Texture* surface;
        SDL_Texture* debuggerSurface;

        SDL_FRect dstRect;



    public:
        Window(std::string title, int width, int height, SDL_WindowFlags flags);
        SDL_Window* getWindow();
        SDL_Surface* getSurface();
        SDL_Surface* getChipSurface();
        void setDebuggerSurface(SDL_Texture* texture);

        void fill(int r, int g, int b);
        SDL_Renderer* getRenderer();
        void drawFromDisplay(bool* display);
        void updateWindow();
        void destroy();
};

class Text
{
    private:
        TTF_Font* font;

    public:
        std::string text;
        SDL_Color color;
};

void setPixel(SDL_Renderer* surf, int x, int y, int r, int g, int b);
Uint32 getPixel(SDL_Surface* surf, int x, int y);

#endif