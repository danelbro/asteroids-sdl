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
    constexpr int rendererFlags = SDL_RENDERER_ACCELERATED;
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
    constexpr double playerEnginePower{ 25.0 };
    constexpr double playerTurnSpeed{ 7.5 };
    constexpr double playerShotPower{ 20.0 };
    constexpr double playerMass{ 150.0 };
    physicsManager.push_back(std::make_unique<PhysicsComponent>(
            playerMass, nullptr )
    );

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
    Vec2d asteroidPos{ player->pos().x - 100, player->pos().y + 100};
    std::vector<Vec2d> asteroidShape{ };
    SdlColor asteroidCol{ 0xff, 0xff, 0xff, 0xff }; // white
    double asteroidScale{ 3.0 };
    double asteroidMass{ 100.0 };
    physicsManager.push_back(std::make_unique<PhysicsComponent>(
            asteroidMass, nullptr )
    );
    double asteroidRadius{ 25.0 };

    entities.push_back(std::make_shared<Asteroid>(&gameWorld, asteroidPos,
                                                  asteroidShape, asteroidCol,
                                                  asteroidScale,
                                                  physicsManager.at(1).get(),
                                                  asteroidRadius, rng));


    // Set up for main loop
    // Structure from http://gameprogrammingpatterns.com/game-loop.html
    std::array<bool, K_TOTAL> keyState{ };
    std::fill(keyState.begin(), keyState.end(), false);

    constexpr double fps{ 60.0 };
    constexpr double msPerFrame { 1000.0 / fps };
    bool isRunning{ true };

    std::ofstream logger("fps.log");
    if (!logger)
        throw std::runtime_error("Couldn't initialise logger");

    auto frameStart{ high_resolution_clock::now() };
    auto frameEnd{ high_resolution_clock::now() };
    while (isRunning) {
        frameStart = high_resolution_clock::now();

        isRunning = processInput(player.get(), keyState);
        updateAll(physicsManager);
        render(entities, renderer.get());

        frameEnd = high_resolution_clock::now();
        auto elapsed{ duration<double, std::milli> {frameEnd - frameStart} };
        double delay = msPerFrame - elapsed.count();
        SDL_Delay(static_cast<uint32_t>( delay > 0 ? delay : 0 ));
        logger << 1000 / elapsed.count() << '\n';
    }
}

int main()
try
{
    // SDL initialisation
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
