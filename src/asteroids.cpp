// Plays an asteroids game
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/Asteroid.hpp"
#include "../inc/Colors.hpp"
#include "../inc/KeyFlag.hpp"
#include "../inc/Entity.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"
#include "SDL_render.h"

extern const SdlColor bg;

std::ofstream errorLogger("exception.log");

void asteroids()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    std::random_device randDev;
    std::mt19937 rng(randDev());
    std::mt19937::result_type seed_val{ static_cast<unsigned long>(std::time(NULL)) };
    rng.seed(seed_val);

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
    constexpr int rendererFlags = SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC;
    renderer = std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer>{
        createRenderer(window.get(), -1, rendererFlags)};

    SDL_SetRenderDrawColor(renderer.get(), bg.r, bg.g, bg.b, bg.a);

    // Gameworld initialisation
    constexpr double fluidDensity{ 0.1 };
    GameWorld gameWorld{ screen, fluidDensity };

    // Make physics manager
    std::vector<std::unique_ptr<PhysicsComponent>> physicsManager{ };

    // Make player
    const Vec2d playerPos{ screen.w / 2.0, screen.h / 2.0 };
    const std::vector<Vec2d> playerShape{ {0, -30}, {20, 30}, {-20, 30} };
    const SdlColor playerCol{ 0xff, 0xff, 0x00, 0xff }; // yellow
    constexpr double playerScale{ 1.0 };
    constexpr double playerEnginePower{ 5000.0 };
    constexpr double playerTurnSpeed{ 300.0 };
    constexpr double playerShotPower{ 5000.0 };
    constexpr double playerMass{ 0.1 };
    physicsManager.push_back(std::make_unique<PhysicsComponent>(
                                 playerMass, nullptr));
    constexpr double playerWarpTimer{ 1.0 };
    constexpr int playerLives{ 3 };
    std::vector<std::shared_ptr<Entity>> entities{ };
    std::shared_ptr<Player> player{
        std::make_shared<Player> (&gameWorld, playerPos,
                                  playerShape, playerCol, playerScale,
                                  playerEnginePower,
                                  playerTurnSpeed,
                                  playerShotPower,
                                  physicsManager.at(0).get(),
                                  playerWarpTimer,
                                  playerLives) };
    entities.push_back(player);

    // Make an asteroid
    double asteroidRadius{ 25.0 };
    Vec2d asteroidPos{ player->pos().x - (asteroidRadius * 2 + 100),
        player->pos().y + (asteroidRadius * 2 + 100) };
    std::vector<Vec2d> asteroidShape{ };
    SdlColor asteroidCol{ 0xff, 0xff, 0xff, 0xff }; // white
    double asteroidScale{ 3.0 };
    double asteroidMass{ 1.0 };
    physicsManager.push_back(std::make_unique<PhysicsComponent>(
                                 asteroidMass, nullptr));
    double asteroidImpulseMin{ 250'000.0 };
    double asteroidImpulseMax{ 500'000.0 };

    entities.push_back(std::make_shared<Asteroid>(&gameWorld, asteroidPos,
                                                  asteroidShape, asteroidCol,
                                                  asteroidScale,
                                                  physicsManager.at(1).get(),
                                                  asteroidImpulseMin,
                                                  asteroidImpulseMax,
                                                  asteroidRadius, rng));


    // Set up for main loop
    // Structure from http://gameprogrammingpatterns.com/game-loop.html
    std::array<bool, K_TOTAL> keyState{ };
    std::fill(keyState.begin(), keyState.end(), false);

    bool isRunning{ true };

    std::ofstream logger("fps.log");
    if (!logger)
        throw std::runtime_error("Couldn't initialise logger");

    double t{ 0.0 };
    const double dt{ 0.01 };

    auto currentTime{ high_resolution_clock::now() };
    double accumulator{ 0.0 };
    while (isRunning) {
        auto newTime{ high_resolution_clock::now() };
        auto frameTime{ duration<double>(newTime - currentTime) };
        currentTime = newTime;

        accumulator += frameTime.count();

        while (accumulator >= dt) {
            isRunning = processInput(player.get(), dt, keyState);
            if (!isRunning) break;
            updateAll(physicsManager, t, dt);
            accumulator -= dt;
            t += dt;
        }

        render(entities, renderer.get());
    }
}

int main()
try
{
    constexpr unsigned sdlFlags = SDL_INIT_VIDEO;
    init(sdlFlags);

    asteroids();

    SDL_Quit();
    return 0;
}
catch (std::exception &e)
{
    errorLogger << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    errorLogger << "unknown exception\n";
    return 2;
}
