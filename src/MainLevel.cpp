#include "MainLevel.hpp"

#include <array>
#include <string>

#include "Box.hpp"
#include "Colors.hpp"
#include "Enemy.hpp"
#include "ScoreManager.hpp"
#include "SDL_Interface.hpp"
#include "Stage.hpp"
#include "PhysicsEntity.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

static constexpr int startingAsteroids{ 3 };
static constexpr double asteroidScale{ 3.0 };
static constexpr int scoreboard_xPos{ 17 };
static constexpr int scoreboard_yPos{ 10 };
static constexpr int font_size{ 28 };
static const std::string font_path{ "data/Play-Regular.ttf" };
static constexpr double fluidDensity{ 0.1 };

MainLevel::MainLevel(const Box& new_screen, uint32_t windowID,
    utl::Renderer& new_renderer)
    : Stage{ new_screen, windowID, new_renderer, utl::StageID::PLAYING },
      font{ utl::createFont(font_path, font_size) },
      gameWorld{ new_screen, fluidDensity },
      rng{ utl::makeSeededRNG() },
      physicsManager{ gameWorld, rng },
      player{ physicsManager.player() },
      scoreManager{ gameWorld, {scoreboard_xPos, scoreboard_yPos},
                    font, new_renderer, player.lives() },
      asteroidsRemain{ false },
      numOfAsteroids{ startingAsteroids }, enemiesRemain{ false },
      levelElapsedTime{ 0.0 }
{
    utl::setRendererDrawColour(renderer(), utl::customCols::bg);
}

utl::StageID MainLevel::handle_input(double, double dt,
    std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(gameWorld, windowID(), key_state);

    if(key_state[utl::KeyFlag::QUIT])
        return utl::StageID::QUIT;
    if (key_state[utl::KeyFlag::K_ESCAPE])
        return utl::StageID::TITLE_SCREEN;

    if (player.isControllable()) {
        if (key_state[utl::KeyFlag::K_UP]) {
            player.engine.on();
        }
        else if (!key_state[utl::KeyFlag::K_UP]) {
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
    return utl::StageID::PLAYING;
}

utl::StageID MainLevel::update(double t, double dt)
{
    constexpr double enemyTime{ 5.0 }; // seconds

    if (!enemiesRemain) levelElapsedTime += dt;

    asteroidsRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type() == utl::EntityFlag::ASTEROID) {
            asteroidsRemain = true;
            break;
        }
    }

    enemiesRemain = false;
    for (auto& ent : physicsManager.physEntities) {
        if (ent->type() == utl::EntityFlag::ENEMY) {
            enemiesRemain = true;
            break;
        }
    }

    if (!asteroidsRemain && !enemiesRemain) {
        for (auto& ent : physicsManager.physEntities) {
            if (ent->type() == utl::EntityFlag::BULLET)
                ent->kill_it();
        }
        levelElapsedTime = 0.0;
        physicsManager.make_asteroids(numOfAsteroids++, asteroidScale, true);
    }

    if (asteroidsRemain && !enemiesRemain && levelElapsedTime >= enemyTime) {
        levelElapsedTime = 0.0;
        physicsManager.make_enemy();
    }

    for (auto& physEnt : physicsManager.physEntities)
        physEnt->physicsComponent.update(dt);

    for (auto& physEnt : physicsManager.physEntities)
        physEnt->update(t, dt);

    physicsManager.checkBulletsHit();
    physicsManager.checkPlayerHit();
    if (player.lives() != scoreManager.lives)
        scoreManager.update_lives(-1);
    physicsManager.clean_up(scoreManager);
    scoreManager.refresh();
    if (player.lives() <= 0) {
        for (auto& physEnt : physicsManager.physEntities) {
            Enemy* eptr{ dynamic_cast<Enemy*>(physEnt.get())};
            if (eptr)
                eptr->playerKilled();
        }
        return utl::StageID::HIGH_SCORES;
    }

    return utl::StageID::PLAYING;
}

void MainLevel::render(double, double)
{
    utl::clearScreen(renderer());
    for (auto& physEntity : physicsManager.physEntities){
        physEntity->render(renderer());
    }
    for (auto& textObject : scoreManager.textObjects) {
        textObject.render(renderer());
    }
    utl::presentRenderer(renderer());
}
