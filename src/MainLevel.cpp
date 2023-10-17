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
#include "../inc/FlagEnums.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/ScoreManager.hpp"
#include "../inc/StageManager.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Player.hpp"
#include "../inc/utility.hpp"

MainLevel::MainLevel(Box new_screen, Uint32 windowID, SDL_Renderer* new_renderer)
    : Stage{new_screen, windowID, new_renderer}, gameWorld{}, physicsManager{}, 
    scoreManager{}, rng{}, font{ nullptr }, player{ nullptr }, 
    asteroidsRemain{ false }, numOfAsteroids{ 3 }
{
    constexpr double fluidDensity{ 0.1 };
    gameWorld.screen = screen();
    gameWorld.fluidDensity = fluidDensity;

    std::random_device randDev;
    rng = std::mt19937{randDev()};
    std::mt19937::result_type seed_val{
        static_cast<unsigned long>(std::time(nullptr))
    };
    rng.seed(seed_val);

    // Make ScoreManager
    constexpr int SCOREBOARD_XPOS{ 17 };
    constexpr int SCOREBOARD_YPOS{ 10 };
    constexpr int FONT_SIZE{ 28 };
    const std::string FONT_PATH{ "data/Play-Regular.ttf" };

    font = std::unique_ptr<TTF_Font, utl::sdl_deleter>(
        utl::createFont(FONT_PATH, FONT_SIZE));

    scoreManager = ScoreManager{ &gameWorld, {SCOREBOARD_XPOS, SCOREBOARD_YPOS},
                                 font.get(), renderer()};

    // Make Player
    player = physicsManager.make_player(&gameWorld);
    if(!player)
        throw std::runtime_error("failed to make player");

    // Add some Asteroids
    physicsManager.make_asteroids(&gameWorld, numOfAsteroids, 3.0, 'n', rng,
                                  player);

    // Add an enemy
    physicsManager.make_enemy(&gameWorld);

    SDL_SetRenderDrawColor(renderer(), customCols::bg.r, customCols::bg.g,
           customCols::bg.b, customCols::bg.a);
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

    if (key_state[static_cast<size_t>(KeyFlag::K_UP)]) {
        if (player)
            player->engine.on();
    }
    else if (!key_state[static_cast<size_t>(KeyFlag::K_UP)]) {
        if (player)
            player->engine.off();
    }
    if (key_state[static_cast<size_t>(KeyFlag::K_LEFT)]) {
        if (player)
            player->engine.turnLeft(dt);
    }
    if (key_state[static_cast<size_t>(KeyFlag::K_RIGHT)]) {
        if (player)
            player->engine.turnRight(dt);
    }
    if (key_state[static_cast<size_t>(KeyFlag::K_SPACE)]) {
        if (player)
            if (!player->gun.fired)
                player->gun.fire(&gameWorld, &physicsManager, player);
    }
    if (!key_state[static_cast<size_t>(KeyFlag::K_SPACE)])
        if (player)
            player->gun.fired = false;

    if (key_state[static_cast<size_t>(KeyFlag::K_LSHIFT)])
        if (player)
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
    
    for (auto& physComp : physicsManager.physMan)
        physComp->update(dt);

    for (auto& physEnt : physicsManager.physEntities)
        physEnt->update(t, dt);

    bool playerIsAlive{ physicsManager.check_player_hit() };
    physicsManager.check_asteroids_hit();

    physicsManager.clean_up(&gameWorld, &scoreManager, rng);

    scoreManager.refresh();

    if (!playerIsAlive) {
        player = nullptr;
        return StageID::HIGH_SCORES;
    }

    return StageID::PLAYING;
}

void MainLevel::render(double, double)
{
    SDL_RenderClear(renderer());
    for (auto& physEntity : physicsManager.physEntities){
        if (physEntity)
            physEntity->render(renderer());
    }
    for (auto& textObject : scoreManager.textObjects) {
        if (textObject)
            textObject->render(renderer());
    }

    SDL_RenderPresent(renderer());
}
