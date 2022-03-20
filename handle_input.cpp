#include "handle_input.h"

#include <SDL.h>

void handle_input(bool *running, SDL_Rect *dest, int vel)
{
    SDL_Event ev;

    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
            *running = false;
        }
        else if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
                *running = false;
                break;
            case SDLK_LEFT:
                dest->x -= vel;
                break;
            case SDLK_RIGHT:
                dest->x += vel;
                break;
            case SDLK_UP:
                dest->y -= vel;
                break;
            case SDLK_DOWN:
                dest->y += vel;
                break;
            default:
                break;
            }
        }
    }
}
