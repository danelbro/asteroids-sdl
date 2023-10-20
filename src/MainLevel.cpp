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

static constexpr int startingAsteroids{ 3 };
static constexpr double asteroidScale{ 3.0 };
static constexpr int scoreboard_xPos{ 17 };
static constexpr int scoreboard_yPos{ 10 };
static constexpr int font_size{ 28 };
static const std::string font_path{ "data/Play-Regular.ttf" };
static constexpr double fluidDensity{ 0.1 };

static std::mt19937 makeSeededRNG()
{
    std::random_device randDev;
    auto rng = std::mt19937{ randDev() };
    std::mt19937::result_type seed_val{
        static_cast<unsigned long>(std::time(nullptr))
    };
    rng.seed(seed_val);

    return rng;
}

MainLevel::MainLevel(Box new_screen, Uint32 windowID,
    SDL_Renderer* new_renderer)
    : Stage{new_screen, windowID, new_renderer},
    gameWorld{ new_screen, fluidDensity },
    font{ std::unique_ptr<TTF_Font, utl::sdl_deleter>(
        utl::createFont(font_path, font_size)) },
    physicsManager{},
    scoreManager{ gameWorld, {scoreboard_xPos, scoreboard_yPos},
                  font.get(), new_renderer},
    rng{ makeSeededRNG() },
    player{ nullptr }, asteroidsRemain{ false },
    numOfAsteroids{ startingAsteroids }
{
    init();
}

void MainLevel::init()
{
    if (!font) throw(utl::SdlException{ "Failed to make font! TTF_Error: " });

    // Make Player
    player = physicsManager.make_player(gameWorld);
    if (!player)
        throw std::runtime_error("failed to make player");

    SDL_SetRenderDrawColor(renderer(), customCols::bg.r, customCols::bg.g,
        customCols::bg.b, customCols::bg.a);
}

StageID MainLevel::handle_input(double, double dt,
    std::array<bool, KeyFlag::K_TOTAL>& key_state)
{
    GameLoop::process_input(gameWorld, windowID(), key_state);

    if(key_state[KeyFlag::QUIT])
        return StageID::QUIT;
    if (key_state[KeyFlag::K_ESCAPE])
        return StageID::TITLE_SCREEN;

    if (key_state[KeyFlag::K_UP]) {
        if (player)
            player->engine.on();
    }
    else if (!key_state[KeyFlag::K_UP]) {
        if (player)
            player->engine.off();
    }
    if (key_state[KeyFlag::K_LEFT]) {
        if (player)
            player->engine.turnLeft(dt);
    }
    if (key_state[KeyFlag::K_RIGHT]) {
        if (player)
            player->engine.turnRight(dt);
    }
    if (key_state[KeyFlag::K_SPACE]) {
        if (player)
            if (!player->gun.fired)
                player->gun.fire(gameWorld, physicsManager, *player);
    }
    if (!key_state[KeyFlag::K_SPACE])
        if (player)
            player->gun.fired = false;

    if (key_state[KeyFlag::K_LSHIFT])
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
        for (auto& ent : physicsManager.physEntities) {
            if (ent->type == EntityFlag::BULLET)
                ent->kill_it();
        }
        physicsManager.make_asteroids(gameWorld, numOfAsteroids++,
                                      asteroidScale,
                                      true, rng, player);
    }

    // Add an enemy
    //physicsManager.make_enemy(gameWorld, rng, player);

    for (auto& physComp : physicsManager.physMan)
        physComp->update(dt);

    for (auto& physEnt : physicsManager.physEntities)
        physEnt->update(t, dt);

    bool playerIsAlive{ physicsManager.check_player_hit() };
    physicsManager.check_shots_hit();

    physicsManager.clean_up(gameWorld, scoreManager, rng);

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
