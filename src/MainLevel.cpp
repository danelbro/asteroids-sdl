﻿#include "MainLevel.hpp"

#include "Colors.hpp"
#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "constants.hpp"
#include "flags.hpp"

#include <array>
#include <memory>
#include <string>
#include <utl_Box.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_random.hpp>

MainLevel::MainLevel(utl::Box& new_screen, uint32_t windowID,
                     utl::Renderer& new_renderer, utl::RNG& newRng)
    : utl::Stage{new_screen, windowID, new_renderer,
                 STAGE_MAP.at(STAGE_ID::PLAYING)},
      font{utl::createFont(constants::fontPath,
                           constants::mainLevelScoreboardFontSize)},
      gameWorld{new_screen, constants::fluidDensity}, rng{newRng},
      physicsManager{gameWorld, rng}, player{physicsManager.player()},
      scoreManager{gameWorld,
                   {constants::mainLevelScoreboardXPos,
                    constants::mainLevelscoreboardYPos},
                   font,
                   new_renderer,
                   player.lives()},
      areAsteroidsRemaining{false},
      numOfAsteroids{constants::initialNumOfAsteroids},
      areEnemiesRemaining{false}, enemyTimer{0.0}
{
    utl::setRendererDrawColour(renderer(), customCols::bg);
}

std::string
MainLevel::handle_input(double, double dt,
                        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(screen(), windowID(), key_state);

    if (key_state[utl::KeyFlag::WINDOW_CHANGE]) {
        gameWorld.screen = screen();
    }

    if (key_state[utl::KeyFlag::QUIT]) {
        return STAGE_MAP.at(STAGE_ID::QUIT);
    }

    if (key_state[utl::KeyFlag::K_ESCAPE]) {
        return STAGE_MAP.at(STAGE_ID::TITLE_SCREEN);
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
    return STAGE_MAP.at(STAGE_ID::PLAYING);
}

void MainLevel::check_targets_cleared()
{
    areAsteroidsRemaining = physicsManager.do_entities_remain_of_type(
        ENTITY_FLAG::ASTEROID, physicsManager.physEntities);

    areEnemiesRemaining = physicsManager.do_entities_remain_of_type(
        ENTITY_FLAG::ENEMY, physicsManager.physEntities);
}

void MainLevel::tick_enemy_timer(const double& dt)
{
    if (!areEnemiesRemaining) {
        enemyTimer += dt;
    }
}

void MainLevel::progress_level()
{
    if (!areAsteroidsRemaining && !areEnemiesRemaining) {
        physicsManager.kill_entities_of_type(ENTITY_FLAG::BULLET,
                                             physicsManager.physEntities);
        physicsManager.kill_entities_of_type(ENTITY_FLAG::ENEMY_BULLET,
                                             physicsManager.physEntities);
        enemyTimer = 0.0;
        physicsManager.make_asteroids(numOfAsteroids++,
                                      constants::initialAsteroidScale, true);
    }
}

void MainLevel::spawn_enemy(const double& enemyTime)
{
    if (areAsteroidsRemaining && !areEnemiesRemaining
        && enemyTimer >= enemyTime) {
        enemyTimer = 0.0;
        physicsManager.make_enemy();
    }
}

void MainLevel::update_physics(const double& dt)
{
    for (auto& physEnt : physicsManager.physEntities) {
        physEnt->physicsComponent.update(dt);
    }
}

void MainLevel::update_entities(const double& t, const double& dt)
{
    for (auto& physEnt : physicsManager.physEntities) {
        physEnt->update(t, dt);
    }
}

void MainLevel::update_scoreboard_lives()
{
    if (player.lives() != scoreManager.lives) {
        scoreManager.update_lives(-1);
    }
}

std::string MainLevel::check_game_over()
{
    if (player.lives() <= 0) {
        for (auto& physEnt : physicsManager.physEntities) {
            if (physEnt->type() == ENTITY_MAP.at(ENTITY_FLAG::ENEMY)) {
                Enemy* enemyPtr{static_cast<Enemy*>(physEnt.get())};
                enemyPtr->playerKilled();
            }
        }
        return STAGE_MAP.at(STAGE_ID::GAME_OVER);
    }
    return STAGE_MAP.at(STAGE_ID::PLAYING);
}

std::string MainLevel::update(double t, double dt)
{
    check_targets_cleared();
    tick_enemy_timer(dt);
    spawn_enemy(constants::enemyTimeSecs);
    progress_level();

    update_physics(dt);
    update_entities(t, dt);

    physicsManager.check_bullet_hits(false);
    physicsManager.check_player_hit();
    update_scoreboard_lives();
    physicsManager.clean_up(scoreManager, false);
    scoreManager.refresh();
    return check_game_over();
}

void MainLevel::render_entities()
{
    for (auto& physEntity : physicsManager.physEntities) {
        physEntity->render(renderer());
    }
}

void MainLevel::render_text()
{
    for (auto& textObject : scoreManager.textObjects) {
        textObject.render(renderer());
    }
}

void MainLevel::render(double, double)
{
    utl::clearScreen(renderer());
    render_entities();
    render_text();
    utl::presentRenderer(renderer());
}
