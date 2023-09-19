#include "../inc/utility.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

const char* SdlException::what() const throw() {
    return SDL_GetError();
}

void init(Uint32 sdlFlags)
{
    if (SDL_Init(sdlFlags) != 0)
        throw SdlException();

    if (TTF_Init() == -1)
        throw SdlException();
}

SDL_Window* createWindow(const char* title, int x, int y,
                          int w, int h, Uint32 flags)
{
    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(title, x, y, w, h ,flags);

    if (!window)
        throw SdlException();

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags)
{
    SDL_Renderer *rend = nullptr;
    rend = SDL_CreateRenderer(window, index, flags);

    if (!rend)
        throw SdlException();

    return rend;
}
