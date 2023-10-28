#include "../inc/MainLevel.hpp"

#include <algorithm>
#include <array>
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
#include "../inc/Stage.hpp"
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

MainLevel::MainLevel(Box new_screen, Uint32 windowID,
    SDL_Renderer* new_renderer)
    : Stage{ new_screen, windowID, new_renderer, StageID::PLAYING },
      gameWorld{ new_screen, fluidDensity },
      font{ utl::createFont(font_path, font_size) },
      physicsManager{},
      scoreManager{ gameWorld, {scoreboard_xPos, scoreboard_yPos},
                  font.get(), new_renderer},
      rng{ makeSeededRNG() },
      player{ nullptr }, asteroidsRemain{ false },
      numOfAsteroids{ startingAsteroids }, enemiesRemain{ false },
      levelElapsedTime{ 0.0 }
{
    init();
}

void MainLevel::init()
{
    if (!font) throw(utl::SdlException{ "Failed to make font! TTF_Error: " });

    // Make Player
    player = physicsManager.make_player(gameWorld, rng);
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

    if (player && player->isControllable()) {
        if (key_state[KeyFlag::K_UP]) {
            player->engine.on();
        }
        else if (!key_state[KeyFlag::K_UP]) {
            player->engine.off();
        }
        if (key_state[KeyFlag::K_LEFT]) {
            player->engine.turnLeft(dt);
        }
        if (key_state[KeyFlag::K_RIGHT]) {
            player->engine.turnRight(dt);
        }
        if (key_state[KeyFlag::K_SPACE]) {
            if (!player->gun.fired)
                player->gun.fire(gameWorld, physicsManager);
        }
        if (!key_state[KeyFlag::K_SPACE]) {
            player->gun.fired = false;
        }
        if (key_state[KeyFlag::K_LSHIFT]) {
            player->hyperdrive.warp();
        }
    }
    return StageID::PLAYING;
}

StageID MainLevel::update(double t, double dt)
{
    constexpr double enemyTime{ 5.0 }; // seconds

    if (!enemiesRemain) levelElapsedTime += dt;

    asteroidsRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type == EntityFlag::ASTEROID) {
            asteroidsRemain = true;
            break;
        }
    }

    enemiesRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type == EntityFlag::ENEMY) {
            enemiesRemain = true;
            break;
        }
    }

    if (!asteroidsRemain && !enemiesRemain) {
        for (auto& ent : physicsManager.physEntities) {
            if (ent->type == EntityFlag::BULLET)
                ent->kill_it();
        }
        levelElapsedTime = 0.0;
        physicsManager.make_asteroids(gameWorld, numOfAsteroids++,
                                      asteroidScale,
                                      true, rng, player);
    }

    if (asteroidsRemain && !enemiesRemain && levelElapsedTime >= enemyTime) {
        levelElapsedTime = 0.0;
        physicsManager.make_enemy(gameWorld, rng, player);
    }

    for (auto& physComp : physicsManager.physMan)
        physComp->update(dt);

    for (auto& physEnt : physicsManager.physEntities)
        physEnt->update(t, dt);

    physicsManager.checkBulletsHit();
    physicsManager.checkPlayerHit(player);
    bool playerWasKilled{physicsManager.wasPlayerKilled(player)};
    physicsManager.clean_up(gameWorld, scoreManager, rng);
    scoreManager.refresh();
    if (playerWasKilled) {
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
        textObject.render(renderer());
    }

    SDL_RenderPresent(renderer());
}
