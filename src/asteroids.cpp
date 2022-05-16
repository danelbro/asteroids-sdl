// Plays an asteroids game
#include <algorithm>
#include <array>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "../inc/Colors.hpp"
#include "../inc/DirFlag.hpp"
#include "../inc/Entity.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

extern const SdlColor bg;

void asteroids()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    // Window initialisation
    std::unique_ptr<SDL_Window, SDL_WindowDestroyer> window{ nullptr };
    char title[] = "Asteroids";
    const Box screen{ 960, 720 };
    constexpr unsigned windowFlags = 0;
    window = std::unique_ptr<SDL_Window, SDL_WindowDestroyer>{
        createWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     screen.w, screen.h, windowFlags)};

    // Renderer intialisation
    std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer> renderer{ nullptr };
    constexpr int rendererFlags = SDL_RENDERER_ACCELERATED;
    renderer = std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer>{
        createRenderer(window.get(), -1, rendererFlags)};

    SDL_SetRenderDrawColor(renderer.get(), bg.r, bg.g, bg.b, bg.a);

    // Gameworld initialisation
    constexpr double fluidDensity{ 0.1 };
    GameWorld gameWorld{ screen, fluidDensity };

    // Make player
    std::vector<std::unique_ptr<Entity>> entities{ };
    entities.push_back(std::make_unique<Player>("assets/player-0.png",
                                                renderer.get(),
                                                gameWorld));

    // Set up for main loop
    // Structure from http://gameprogrammingpatterns.com/game-loop.html
    std::array<bool, K_TOTAL> keyState{ };
    std::fill(keyState.begin(), keyState.end(), false);

    constexpr double fps { 1000.0 / 60 };
    double lag{ 0.0 };
    bool isRunning{ true };

    auto previous{ high_resolution_clock::now() };
    while (isRunning) {
        auto current{ high_resolution_clock::now() };
        auto elapsed{ duration<double, std::milli> {current - previous} };
        previous = current;
        lag += elapsed.count();

        isRunning = handleInput(entities, keyState);

        while (lag >= fps)
        {
            updateAll(entities, keyState);
            lag -= fps;
        }

        render(entities, renderer.get(), lag / fps);
    }
}

int main()
try
{
    // SDL initialisation
    constexpr unsigned sdlFlags = SDL_INIT_VIDEO;
    constexpr unsigned imgFlags = IMG_INIT_PNG;
    init(sdlFlags, imgFlags);

    asteroids();

    SDL_Quit();
    return 0;
}
catch (std::exception &e)
{
    std::cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    std::cerr << "unknown exception\n";
    return 2;
}
