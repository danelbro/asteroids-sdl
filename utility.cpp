#include <SDL.h>

#include "SDL_Exception.h"
#include "utility.h"

void init(Uint32 flags)
{
    if (SDL_Init(flags) != 0)
        throw SDL_Exception();
}

SDL_Window* create_window(const char* title, int x, int y,
                          int w, int h, Uint32 flags)
{
    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(title, x, y, w, h ,flags);

    if (!window)
        throw SDL_Exception();

    return window;
}

SDL_Renderer* create_renderer(SDL_Window* window, int index, Uint32 flags)
{
    SDL_Renderer *rend = nullptr;
    rend = SDL_CreateRenderer(window, index, flags);

    if (!rend)
        throw SDL_Exception();

    return rend;
}

void close(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
