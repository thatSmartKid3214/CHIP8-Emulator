#include "../include/wrapper.h"

int R = 0;
int G = 0;
int B = 0;

int init(SDL_InitFlags flags)
{
    return (SDL_Init(flags) && TTF_Init());
}

void quit()
{
    TTF_Quit();
    SDL_Quit();
}

Window::Window(std::string title, int width, int height, SDL_WindowFlags flags)
{
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, flags, &win, &renderer);

    surface = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);

    SDL_SetRenderTarget(renderer, surface);

    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = width/1.8;
    dstRect.h = height/1.8;
}

void Window::updateWindow()
{

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderTexture(renderer, debuggerSurface, NULL, NULL);
    SDL_RenderTexture(renderer, surface, NULL, &dstRect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderRect(renderer, &dstRect);

    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, surface);
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}

void Window::destroy()
{
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(surface);

    win = NULL;
    renderer = NULL;
    surface = NULL;
}

void Window::setDebuggerSurface(SDL_Texture* texture)
{
    debuggerSurface = texture;
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
