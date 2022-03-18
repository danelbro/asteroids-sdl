#include <SDL.h>

#include "handle_input.h"

void handle_input(bool *running)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
            *running = false;
        }
        else if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_ESCAPE) {
                *running = false;
            }
        }
    }
}
