#include "../inc/utility.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

SdlException::SdlException(std::string message)
    : std::runtime_error{message}
{}

void init(Uint32 sdlFlags)
{
    if (SDL_Init(sdlFlags) != 0)
        throw SdlException(std::string{"Cannot initialise SDL! SDL_Error: ", SDL_GetError()});

    if (TTF_Init() == -1)
        throw SdlException(std::string{"Cannot initialise SDL_TTF! TTF_Error: ", TTF_GetError()});
}

SDL_Window* createWindow(const char* title, int x, int y,
                          int w, int h, Uint32 flags)
{
    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(title, x, y, w, h ,flags);

    if (!window)
        throw SdlException(std::string{"Cannot create window! SDL_Error: ", SDL_GetError()});

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags)
{
    SDL_Renderer *rend = nullptr;
    rend = SDL_CreateRenderer(window, index, flags);

    if (!rend)
        throw SdlException(std::string{"Cannot create renderer! SDL_Error: ", SDL_GetError()});

    return rend;
}
