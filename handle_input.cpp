#include "handle_input.hpp"

#include <SDL.h>

void handle_input(bool &running, std::vector<bool> &key_state)
{
    SDL_Event ev;


    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
            running = false;
        }
        else if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
                running = false;
                break;
            case SDLK_LEFT:
                key_state[DIR_LEFT] = true;
                break;
            case SDLK_RIGHT:
                key_state[DIR_RIGHT] = true;
                break;
            case SDLK_UP:
                key_state[DIR_UP] = true;
                break;
            case SDLK_DOWN:
                key_state[DIR_DOWN] = true;
                break;
            default:
                break;
            }
        }
        else if (ev.type == SDL_KEYUP) {
            switch (ev.key.keysym.sym) {
            case SDLK_LEFT:
                key_state[DIR_LEFT] = false;
                break;
            case SDLK_RIGHT:
                key_state[DIR_RIGHT] = false;
                break;
            case SDLK_UP:
                key_state[DIR_UP] = false;
                break;
            case SDLK_DOWN:
                key_state[DIR_DOWN] = false;
                break;
            default:
                break;
            }
        }
    }
}
