#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <string>
#include <vector>

#include <SDL.h>

// wrapper around std::exception to make SDL exception handling smoother
class Sdl_exception : public std::exception
{
    const char* what() const throw();
};

// wrapper around std::exception to make SDL_image exception handling smoother
class Img_exception : public std::exception
{
    const char* what() const throw();
};

// Initialise SDL and SDL_image with flags.
// Throw an exception if initialisation fails
void init(Uint32 sdl_flags, Uint32 img_flags);

// Create an SDL_Window*. Throw an Sdl_exception if creation fails
SDL_Window* create_window(const char *title, int x, int y,
                          int w, int h, Uint32 flags);

// Create an SDL_Renderer*. Throw an Sdl_exception if creation fails
SDL_Renderer* create_renderer(SDL_Window *window, int index, Uint32 flags);

// Load an image from path into texture on renderer, with an associated rect
SDL_Texture* load_media(std::string path, SDL_Renderer* renderer,
                        SDL_Texture *texture);

// Free SDL resources
void close(SDL_Renderer *renderer, SDL_Window *window,
           std::vector<SDL_Texture*> textures);

#endif
