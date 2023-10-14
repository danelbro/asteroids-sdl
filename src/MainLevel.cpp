#include "../inc/MainLevel.hpp"

#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Box.hpp"
#include "../inc/Entity.hpp"
#include "../inc/EntityManager.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/StageManager.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Player.hpp"
#include "../inc/utility.hpp"

void MainLevel::init()
{
    // Gameworld initialisation
    constexpr double fluidDensity{ 0.1 };
    gameWorld = { m_screen, fluidDensity };

    // refresh EntityManager
    entityManager = EntityManager{};

    // refresh PhysicsManager
    physicsManager = PhysicsManager{};

    // Make ScoreManager
    TTF_Font* font{ nullptr };

    constexpr int SCOREBOARD_XPOS{ 17 };
    constexpr int SCOREBOARD_YPOS{ 10 };

    font = TTF_OpenFont("data/Play-Regular.ttf", 28);
    if (!font) {
        throw SdlException(std::string{"Couldn't load font! TTF_Error:", TTF_GetError()});
    }
    scoreManager = ScoreManager{ &gameWorld, {SCOREBOARD_XPOS, SCOREBOARD_YPOS},
                               font, m_rend };

    // Make Player
    Player* player{physicsManager.make_player(&gameWorld)};

    bool asteroidsRemain{ false };
    int numOfAsteroids{ 3 };
    physicsManager.make_asteroids(&gameWorld, numOfAsteroids, 3.0, 'n', rng, player);
}

StageID MainLevel::handle_input()
{
    return StageID::PLAYING;
}

StageID MainLevel::update()
{
    return StageID::PLAYING;
}

void MainLevel::render()
{}

void asteroids(Box screen, unsigned windowID, SDL_Renderer* renderer)
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    // Set up for main loop
    // Structure from http://gameprogrammingpatterns.com/game-loop.html
    std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)> keyState{ };
    std::fill(keyState.begin(), keyState.end(), false);

    bool isRunning{ true };

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
            asteroidsRemain = false;
            for (auto& ent : physicsManager.physEntities) {
                if (ent->type == EntityFlag::ASTEROID)
                    asteroidsRemain = true;
            }
            if (!asteroidsRemain) {
                numOfAsteroids++;
                for (auto& ent : physicsManager.physEntities) {
                    if (ent->type == EntityFlag::BULLET)
                        ent->kill_it();
                }
                physicsManager.make_asteroids(&gameWorld, numOfAsteroids, 3.0, 'n',
                                              rng, player);
            }

            isRunning = processInput(&gameWorld, windowID, player, dt,
                keyState, &physicsManager);
            if (!isRunning) break;
            isRunning = updateAll(&gameWorld, &entityManager, &physicsManager,
                                  &scoreManager, t, dt, rng);
            if (!isRunning) break;
            accumulator -= dt;
            t += dt;
        }

        render(&entityManager, &physicsManager, &scoreManager, renderer);
    }
}
