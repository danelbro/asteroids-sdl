// Plays an asteroids game

#include <iostream>
#include <SDL.h>

using std::cout;    using std::endl;

void handle_input(bool *running);
void close(SDL_Renderer* renderer, SDL_Window* window);

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
        return -1;
    }

    const int SCREEN_WIDTH = 960;
    const int SCREEN_HEIGHT = 540;
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    window = SDL_CreateWindow("Asteroids",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              0);
    if (!window) {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        cout << "Failed to create renderer: " << SDL_GetError() << endl;
        return -1;
    }

    // set background color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    bool still_running = true;
    while (still_running) {
        SDL_RenderClear(renderer);
        handle_input(&still_running);
        SDL_RenderPresent(renderer);
    }

    close(renderer, window);

    return 0;
}

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

void close(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
