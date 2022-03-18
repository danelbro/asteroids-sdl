#ifndef UTILITY_H
#define UTILITY_H

#include <SDL.h>

// Initialise SDL with flags. Throw an SDL_Exception if initialisation fails
void init(Uint32 flags);

// Create an SDL_Window*. Throw an SDL_Exception if creation fails
SDL_Window* create_window(const char *title, int x, int y,
                          int w, int h, Uint32 flags);

// Create an SDL_Renderer*. Throw an SDL_Exception if creation fails
SDL_Renderer* create_renderer(SDL_Window *window, int index, Uint32 flags);

// Free SDL resources
void close(SDL_Renderer *renderer, SDL_Window *window);

#endif
