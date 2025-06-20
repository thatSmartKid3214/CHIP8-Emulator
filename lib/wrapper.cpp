#include "../include/wrapper.h"

int R = 0;
int G = 0;
int B = 0;

int init(SDL_InitFlags flags)
{
    return SDL_Init(flags);
}

void quit()
{
    SDL_Quit();
}

Window::Window(std::string title, int width, int height, SDL_WindowFlags flags)
{
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, flags, &win, &renderer);
}

void Window::updateWindow()
{
    SDL_RenderPresent(renderer);
}

void Window::destroy()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);

    win = NULL;
    renderer = NULL;
}

void Window::fill(int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

SDL_Window* Window::getWindow()
{
    return win;
}

void Window::drawFromDisplay(bool* display)
{
    int row = 0;
    int size = WIDTH*HEIGHT;

    for(int i = 0; i < size; i++)
    {
        if(i%WIDTH == 0 && i != 0)
        {
            row += 1;
        }

        if(display[i] == true)
        {
            setPixel(renderer, i%WIDTH, row, 255, 255, 255);
        }

    }
}


void setPixel(SDL_Renderer* renderer, int x, int y, int r, int g, int b)
{
    SDL_FRect rect;
    rect.x = x*SCALE;
    rect.y = y*SCALE;
    rect.w = SCALE;
    rect.h = SCALE;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);

}

Uint32 getPixel(SDL_Surface* surf, int x, int y)
{
    return 0;
}



