#pragma once

#include <stdexcept>
#include <string>

#include <SDL.h>

struct SDL_WindowDestroyer
{
    void operator()(SDL_Window* w) const
    {
        SDL_DestroyWindow(w);
    }
};

struct SDL_RendererDestroyer
{
    void operator()(SDL_Renderer* r) const
    {
        SDL_DestroyRenderer(r);
    }
};

// wrapper around std::runtime_error to make SDL exception handling smoother
class SdlException : public std::runtime_error
{
public:
    SdlException(std::string e);
};

// Initialise SDL with sdlFlags.
// Throw SdlException if initialisation fails
void init(Uint32 sdlFlags);

// Create an SDL_Window*. Throw an SdlException if creation fails
SDL_Window* createWindow(const char *title, int x, int y,
                          int w, int h, Uint32 flags);

// Create an SDL_Renderer*. Throw an SdlException if creation fails
SDL_Renderer* createRenderer(SDL_Window *window, int index, Uint32 flags);
