// Plays an asteroids game
#include "handle_input.h"
#include "utility.h"

#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

int main()
{
    try {
        const unsigned sdl_flags = SDL_INIT_VIDEO;
        const unsigned img_flags = IMG_INIT_PNG;
        init(sdl_flags, img_flags);

        SDL_Window *window = nullptr;
        const std::string title = "Asteroids";
        const int screen_width = 960;
        const int screen_height = 720;
        const unsigned window_flags = 0;

        window = create_window(title.c_str(),
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               screen_width, screen_height,
                               window_flags);

        SDL_Renderer *renderer = nullptr;
        const int renderer_flags = SDL_RENDERER_ACCELERATED;

        renderer = create_renderer(window, -1, renderer_flags);

        SDL_SetRenderDrawColor(renderer, 0x10, 0x13, 0x26, 0xff);

        SDL_Texture* player = nullptr;
        player = load_media("player-0.png", renderer, player);

        std::vector<SDL_Texture*> textures;
        textures.push_back(player);

        SDL_Rect player_rect;
        SDL_QueryTexture(player, NULL, NULL, &player_rect.w, &player_rect.h);

        player_rect.x = (screen_width / 2) - (player_rect.w / 2);
        player_rect.y = (screen_height / 2) - (player_rect.h / 2);

        int player_velocity = 10;
        SDL_Rect dest;

        bool running = true;
        const double fps = 1000.0 / 60;
        while (running) {
            SDL_RenderClear(renderer);

            dest = player_rect;
            handle_input(&running, &dest, player_velocity);

            if (dest.x < 0)
                player_rect.x = 0;
            else if (dest.x > screen_width - dest.w)
                player_rect.x = screen_width - dest.w;
            else
                player_rect.x = dest.x;

            if (dest.y < 0)
                player_rect.y = 0;
            else if (dest.y > screen_height - dest.h)
                player_rect.y = screen_height - dest.h;
            else
                player_rect.y = dest.y;

            SDL_RenderCopy(renderer, player, NULL, &player_rect);

            SDL_RenderPresent(renderer);
            SDL_Delay(fps);
        }

        close(renderer, window, textures);

        return 0;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}
