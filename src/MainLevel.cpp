#include "MainLevel.hpp"

#include "Colors.hpp"
#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "flags.hpp"

#include <array>
#include <string>
#include <utl_Box.hpp>
#include <utl_PhysicsEntity.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_utility.hpp>

static constexpr int startingAsteroids{3};
static constexpr double asteroidScale{3.0};
static constexpr int scoreboard_xPos{17};
static constexpr int scoreboard_yPos{10};
static constexpr int font_size{28};
static const std::string font_path{"data/Play-Regular.ttf"};
static constexpr double fluidDensity{0.1};

MainLevel::MainLevel(utl::Box& new_screen, uint32_t windowID,
                     utl::Renderer& new_renderer)
    : utl::Stage{new_screen, windowID, new_renderer,
                 STAGE_MAP[STAGE_ID::PLAYING]},
      font{utl::createFont(font_path, font_size)},
      gameWorld{new_screen, fluidDensity}, rng{utl::makeSeededRNG()},
      physicsManager{gameWorld, rng}, player{physicsManager.player()},
      scoreManager{gameWorld,
                   {scoreboard_xPos, scoreboard_yPos},
                   font,
                   new_renderer,
                   player.lives()},
      asteroidsRemain{false}, numOfAsteroids{startingAsteroids},
      enemiesRemain{false}, levelElapsedTime{0.0}
{
    utl::setRendererDrawColour(renderer(), customCols::bg);
}

std::string
MainLevel::handle_input(double, double dt,
                        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(gameWorld.screen, windowID(), key_state);

    if (key_state[utl::KeyFlag::QUIT]) {
        return STAGE_MAP[STAGE_ID::QUIT];
    }

    if (key_state[utl::KeyFlag::K_ESCAPE]) {
        return STAGE_MAP[STAGE_ID::TITLE_SCREEN];
    }

    if (player.isControllable()) {
        if (key_state[utl::KeyFlag::K_UP]) {
            player.engine.on();
        } else if (!key_state[utl::KeyFlag::K_UP]) {
            player.engine.off();
        }
        if (key_state[utl::KeyFlag::K_LEFT]) {
            player.engine.turnLeft(dt);
        }
        if (key_state[utl::KeyFlag::K_RIGHT]) {
            player.engine.turnRight(dt);
        }
        if (key_state[utl::KeyFlag::K_SPACE]) {
            player.gun.fire(physicsManager);
        }
        if (!key_state[utl::KeyFlag::K_SPACE]) {
            player.gun.reset();
        }
        if (key_state[utl::KeyFlag::K_LSHIFT]) {
            player.hyperdrive.warp();
        }
    }
    return STAGE_MAP[STAGE_ID::PLAYING];
}

std::string MainLevel::update(double t, double dt)
{
    constexpr double enemyTimeSecs{5.0};

    if (!enemiesRemain) {
        levelElapsedTime += dt;
    }

    asteroidsRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type() == ENTITY_MAP[ENTITY_FLAG::ASTEROID]) {
            asteroidsRemain = true;
            break;
        }
    }

    enemiesRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY]) {
            enemiesRemain = true;
            break;
        }
    }

    if (!asteroidsRemain && !enemiesRemain) {
        for (auto& ent : physicsManager.physEntities) {
            if (ent->type() == ENTITY_MAP[ENTITY_FLAG::BULLET]) {
                ent->kill_it();
            }
        }
        levelElapsedTime = 0.0;
        physicsManager.make_asteroids(numOfAsteroids++, asteroidScale, true);
    }

    if (asteroidsRemain && !enemiesRemain && levelElapsedTime >= enemyTimeSecs) {
        levelElapsedTime = 0.0;
        physicsManager.make_enemy();
    }

    for (auto& physEnt : physicsManager.physEntities) {
        physEnt->physicsComponent.update(dt);
    }

    for (auto& physEnt : physicsManager.physEntities) {
        physEnt->update(t, dt);
    }

    physicsManager.checkBulletsHit(false);
    physicsManager.checkPlayerHit();
    if (player.lives() != scoreManager.lives) {
        scoreManager.update_lives(-1);
    }
    physicsManager.clean_up(scoreManager, false);
    scoreManager.refresh();
    if (player.lives() <= 0) {
        for (auto& physEnt : physicsManager.physEntities) {
            if (physEnt->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY]) {
                Enemy* eptr{static_cast<Enemy*>(physEnt.get())};
                eptr->playerKilled();
            }
        }
        return STAGE_MAP[STAGE_ID::GAME_OVER];
    }

    return STAGE_MAP[STAGE_ID::PLAYING];
}

void MainLevel::render(double, double)
{
    utl::clearScreen(renderer());
    for (auto& physEntity : physicsManager.physEntities) {
        physEntity->render(renderer());
    }
    for (auto& textObject : scoreManager.textObjects) {
        textObject.render(renderer());
    }
    utl::presentRenderer(renderer());
}
