// Plays an asteroids game

#include <iostream>
#include <string>
#include <exception>

#include <SDL.h>

#include "handle_input.h"
#include "utility.h"

int main()
{
    try {
        const int INIT_FLAGS = SDL_INIT_VIDEO;
        init(INIT_FLAGS);

        SDL_Window *window = nullptr;
        const std::string TITLE = "Asteroids";
        const int SCREEN_WIDTH = 960;
        const int SCREEN_HEIGHT = 540;
        const int WINDOW_FLAGS = 0;

        window = create_window(TITLE.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               WINDOW_FLAGS);

        SDL_Renderer *renderer = nullptr;
        const int RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;

        renderer = create_renderer(window, -1, RENDERER_FLAGS);

        // set background color to white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        bool running = true;
        while (running) {
            SDL_RenderClear(renderer);
            handle_input(&running);
            SDL_RenderPresent(renderer);
        }

        close(renderer, window);

        return 0;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
