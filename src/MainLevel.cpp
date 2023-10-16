#include "../inc/MainLevel.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
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

MainLevel::MainLevel(Box new_screen, Uint32 windowID, SDL_Renderer* new_renderer)
    : Stage{new_screen, windowID, new_renderer}, gameWorld{}, entityManager{},
      physicsManager{}, scoreManager{}, rng{}, font{ nullptr },
      player{ nullptr }, asteroidsRemain{ false }, numOfAsteroids{ 3 }
{
    constexpr double fluidDensity{ 0.1 };
    gameWorld.screen = screen();
    gameWorld.fluidDensity = fluidDensity;

    std::random_device randDev;
    rng = std::mt19937{randDev()};
    std::mt19937::result_type seed_val{
        static_cast<unsigned long>(std::time(NULL))
    };
    rng.seed(seed_val);

    // Make ScoreManager
    constexpr int SCOREBOARD_XPOS{ 17 };
    constexpr int SCOREBOARD_YPOS{ 10 };

    font = TTF_OpenFont("data/Play-Regular.ttf", 28);
    if (!font) {
        throw SdlException(std::string{"Couldn't load font! TTF_Error:",
                                       TTF_GetError()});
    }
    scoreManager = ScoreManager{ &gameWorld, {SCOREBOARD_XPOS, SCOREBOARD_YPOS},
                                 font, renderer() };

    // Make Player
    player = physicsManager.make_player(&gameWorld);
    if(!player)
        throw SdlException("failed to make player");

    // Add some Asteroids
    physicsManager.make_asteroids(&gameWorld, numOfAsteroids, 3.0, 'n', rng,
                                  player);
}

MainLevel::~MainLevel()
{
    TTF_CloseFont(font);
    font = nullptr;
}

StageID MainLevel::handle_input(double, double dt,
                                std::array<bool,
                                static_cast<size_t>(KeyFlag::K_TOTAL)>& key_state)
{
    GameLoop::process_input(&gameWorld, windowID(), key_state);

    if(key_state[static_cast<size_t>(KeyFlag::QUIT)])
        return StageID::QUIT;
    if (key_state[static_cast<size_t>(KeyFlag::K_ESCAPE)])
        return StageID::TITLE_SCREEN;

    if (key_state[static_cast<size_t>(KeyFlag::K_UP)])
        player->engine.on();
    else if (!key_state[static_cast<size_t>(KeyFlag::K_UP)])
        player->engine.off();

    if (key_state[static_cast<size_t>(KeyFlag::K_LEFT)])
        player->engine.turnLeft(dt);
    if (key_state[static_cast<size_t>(KeyFlag::K_RIGHT)])
        player->engine.turnRight(dt);

    if (key_state[static_cast<size_t>(KeyFlag::K_SPACE)])
        if (!player->gun.fired)
            player->gun.fire(&gameWorld, &physicsManager, player);
    if (!key_state[static_cast<size_t>(KeyFlag::K_SPACE)])
        player->gun.fired = false;

    if (key_state[static_cast<size_t>(KeyFlag::K_LSHIFT)])
        player->hyperdrive.warp();

    return StageID::PLAYING;
}

StageID MainLevel::update(double t, double dt)
{
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
        physicsManager.make_asteroids(&gameWorld, numOfAsteroids, 3.0,
                                      'n', rng, player);
    }

    for (auto &ent : entityManager.entities)
        ent->update(t, dt);
    for (auto& physEnt : physicsManager.physEntities)
        physEnt->update(t, dt);

    bool playerIsAlive{ physicsManager.check_player_hit() };
    physicsManager.check_asteroids_hit();

    entityManager.clean_up();
    physicsManager.clean_up(&gameWorld, &scoreManager, rng);

    scoreManager.refresh();

    for (auto &physComp : physicsManager.physMan)
        physComp->update(dt);

    if (!playerIsAlive)
        return StageID::HIGH_SCORES;

    return StageID::PLAYING;
}

void MainLevel::render(double, double)
{
    SDL_RenderClear(renderer());
    for (auto& entity : entityManager.entities) {
        if (entity)
            entity->render(renderer());
    }
    for (auto& physEntity : physicsManager.physEntities){
        if (physEntity)
            physEntity->render(renderer());
    }
    for (auto& textObject : scoreManager.textObjects) {
        textObject.render(renderer());
    }
    SDL_RenderPresent(renderer());
}
