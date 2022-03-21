// Plays an asteroids game
#include <cmath>
#include <chrono>
#include <iostream>
#include <string>
#include <exception>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "handle_input.h"
#include "utility.h"

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

        double player_vel_x = 0.0, player_vel_y = 0.0;
        const double delta_vel = 1.0, max_vel = 15.0;
        SDL_Rect dest;
        std::vector<bool> key_state(DIR_TOTAL, false);

        bool running = true;
        const double fps = 1000.0 / 60;
        while (running) {
            using namespace std::chrono;
            auto start_time = high_resolution_clock().now();
            SDL_RenderClear(renderer);

            dest = player_rect;
            handle_input(running, key_state);

            if (key_state[DIR_LEFT])
                player_vel_x -= delta_vel;
            else if (key_state[DIR_RIGHT])
                player_vel_x += delta_vel;
            if (key_state[DIR_UP])
                player_vel_y -= delta_vel;
            else if (key_state[DIR_DOWN])
                player_vel_y += delta_vel;

            // clamp velocity
            if (player_vel_x < -max_vel)
                player_vel_x = -max_vel;
            else if (player_vel_x > max_vel)
                player_vel_x = max_vel;

            if (player_vel_y < -max_vel)
                player_vel_y = -max_vel;
            else if (player_vel_y > max_vel)
                player_vel_y = max_vel;

            dest.x += player_vel_x;
            dest.y += player_vel_y;

            std::cout << "Player x pos: " << player_rect.x << std::endl
                      << "Player y pos: " << player_rect.y << std::endl
                      << "Player x vel: " << player_vel_x << std::endl
                      << "Player y vel: " << player_vel_y << std::endl;

            // things go through walls in Asteroids
            if (dest.x < -player_rect.w)
                player_rect.x = screen_width;
            else if (dest.x > screen_width)
                player_rect.x = -player_rect.w;
            else
                player_rect.x = dest.x;

            if (dest.y < -player_rect.h)
                player_rect.y = screen_height;
            else if (dest.y > screen_height)
                player_rect.y = -player_rect.h;
            else
                player_rect.y = dest.y;

            // apply friction
            player_vel_x *= 0.95;
            player_vel_y *= 0.95;

            // clamp movement
            if (std::abs(player_vel_x) < 0.3) {
                player_vel_x = 0;
            }
            if (std::abs(player_vel_y) < 0.3) {
                player_vel_y = 0;
            }

            SDL_RenderCopy(renderer, player, NULL, &player_rect);

            SDL_RenderPresent(renderer);
            SDL_Delay(fps);
            auto stop_time = high_resolution_clock().now();
            auto duration = duration_cast<milliseconds>(stop_time - start_time);
            std::cout << "FPS: " << 1000 / duration.count() << std::endl;
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
