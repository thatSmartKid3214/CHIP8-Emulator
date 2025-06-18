#include "../include/wrapper.h"


int init(SDL_InitFlags flags)
{
    return SDL_Init(flags);
}

void quit()
{
    SDL_Quit();
}

void updateWindow(Window win)
{
    
    SDL_BlitSurfaceScaled(win.getChipSurface(), NULL, win.getSurface(), &win.screen_rect, SDL_SCALEMODE_NEAREST);

    SDL_UpdateWindowSurface(win.getWindow());
}

void destroy(Window win)
{
    SDL_DestroyWindow(win.getWindow());
}

Window::Window(std::string title, int width, int height, SDL_WindowFlags flags)
{
    win = SDL_CreateWindow(title.c_str(), width, height, flags);
    screen_rect.x = 0;
    screen_rect.y = 0;
    screen_rect.w = width;
    screen_rect.h = height;

    if(win != NULL)
    {
        surf = SDL_GetWindowSurface(win);
    } else {
        std::cout << "Window was not created successfully" << std::endl;
        quit();
    }
}

void Window::fill(int r, int g, int b)
{
    SDL_FillSurfaceRect(surf, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(surf->format), NULL, r, g, b));
}

SDL_Surface* Window::getChipSurface()
{
    return chipSurf;
}

void fill(SDL_Surface* surf, int r, int g, int b)
{
    SDL_FillSurfaceRect(surf, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(surf->format), NULL, r, g, b));
}

SDL_Window* Window::getWindow()
{
    return win;
}

SDL_Surface* Window::getSurface()
{
    return surf;
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
            setPixel(chipSurf, i%WIDTH, row, 255, 255, 255);
        }

    }
}


void setPixel(SDL_Surface* surf, int x, int y, int r, int g, int b)
{
    Uint32 pixel = SDL_MapRGB(SDL_GetPixelFormatDetails(surf->format), NULL, r, g, b);
    int position = (y*WIDTH) + x;

    if(SDL_MUSTLOCK(surf))
    {
        if(SDL_LockSurface(surf))
        {
            Uint32* pixels = static_cast<Uint32*>(surf->pixels);
            pixels[position] = pixel;

            SDL_UnlockSurface(surf);
        }
    } else {
        Uint32* pixels = static_cast<Uint32*>(surf->pixels);
        pixels[position] = pixel;
    }
}

Uint32 getPixel(SDL_Surface* surf, int x, int y)
{
    Uint32 pixel = -1;

    if(SDL_MUSTLOCK(surf))
    {
        if(SDL_LockSurface(surf))
        {
            int position = (y*surf->pitch) + (x*SDL_BYTESPERPIXEL(surf->format));

            Uint32* pixels = static_cast<Uint32*>(surf->pixels);
            pixel = pixels[position];

            SDL_UnlockSurface(surf);
        }
    } else {
        int position = (y*surf->pitch) + (x*SDL_BYTESPERPIXEL(surf->format));

        Uint32* pixels = static_cast<Uint32*>(surf->pixels);
        pixel = pixels[position];
    }

    return pixel;
}



