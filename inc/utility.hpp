#pragma once

#include <exception>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "Entity.hpp"

// wrapper around std::exception to make SDL exception handling smoother
class SdlException : public std::exception
{
    const char* what() const throw();
};

// wrapper around std::exception to make SDL_image exception handling smoother
class ImgException : public std::exception
{
    const char* what() const throw();
};

// Initialise SDL and SDL_image with flags.
// Throw the relevant exception if initialisation fails
void init(Uint32 sdlFlags, Uint32 imgFlags);

// Create an SDL_Window*. Throw an SdlException if creation fails
SDL_Window* createWindow(const char *title, int x, int y,
                          int w, int h, Uint32 flags);

// Create an SDL_Renderer*. Throw an SdlException if creation fails
SDL_Renderer* createRenderer(SDL_Window *window, int index, Uint32 flags);

// Load an image from path into texture on renderer, with an associated rect
// Throw an ImgException if loading fails.
SDL_Texture* loadMedia(std::string path, SDL_Renderer* renderer);

// Free SDL resources
void close(SDL_Renderer *renderer, SDL_Window *window);
