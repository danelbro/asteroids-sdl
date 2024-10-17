﻿#include "GameOver.hpp"

#include "Colors.hpp"
#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "flags.hpp"

#include <array>
#include <memory>
#include <string>
#include <utl_GameWorld.hpp>
#include <utl_PhysicsEntity.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_utility.hpp>

static const std::string fontPath{"data/Play-Regular.ttf"};
static constexpr int titleFont_size{72};
static constexpr int scoreFont_size{48};
static constexpr double padding{250.0};

GameOver::GameOver(
    utl::Box& screen, uint32_t windowID, utl::Renderer& rend,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
    int score)
    : Stage{screen, windowID, rend, STAGE_MAP[STAGE_ID::GAME_OVER]},
      m_gameWorld{screen, 0.1},
      m_titleFont{utl::createFont(fontPath, titleFont_size)},
      m_scoreFont{utl::createFont(fontPath, scoreFont_size)},
      m_rng{utl::makeSeededRNG()}, m_physMan{m_gameWorld, m_rng},
      m_scoreMan{rend}, m_score{score},
      m_GameOverText{
          m_gameWorld.screen, {}, m_titleFont, customCols::text_col, rend},
      m_ScoreText{
          m_gameWorld.screen, {}, m_scoreFont, customCols::text_col, rend},
      asteroidsRemain{false}
{
    // remove Player from m_physMan
    m_physMan.physEntities.erase(m_physMan.physEntities.begin());

    for (auto& physEnt : physEntities) {
        switch (ENTITY_STRING_MAP[physEnt->type()]) {
        case ENTITY_FLAG::PLAYER:
            break;
        case ENTITY_FLAG::ASTEROID:
            m_physMan.make_asteroid(*physEnt);
            break;
        case ENTITY_FLAG::BULLET:
        case ENTITY_FLAG::ENEMY_BULLET:
            m_physMan.make_bullet(*physEnt);
            break;
        case ENTITY_FLAG::ENEMY:
            m_physMan.make_enemy(*physEnt);
            break;
        default:
            break;
        }

        check_asteroids_cleared();
    }

    m_GameOverText.updateText("Game Over");
    double titleXPos = screen.w / 2.0 - m_GameOverText.size().x / 2.0;
    double titleYPos = screen.h / 3.0;
    m_GameOverText.setPos({titleXPos, titleYPos});

    m_ScoreText.updateText("Score: " + std::to_string(m_score));
    double scoreXPos = screen.w / 2.0 - m_ScoreText.size().x / 2.0;
    double scoreYPos = screen.h - padding - m_ScoreText.size().y;
    m_ScoreText.setPos({scoreXPos, scoreYPos});
}

static void reset_title(utl::TextObject& title)
{
    title.setPos({title.screen().w / 2.0 - title.size().x / 2.0,
                  title.screen().h / 3.0});
}

static void reset_score(utl::TextObject& score)
{
    score.setPos({score.screen().w / 2.0 - score.size().x / 2.0,
                  score.screen().h - padding - score.size().y});
}

std::string
GameOver::handle_input(double, double,
                       std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(screen(), windowID(), key_state);

    if (key_state[utl::KeyFlag::WINDOW_CHANGE]) {
        m_gameWorld.screen = screen();
    }

    if (key_state[utl::KeyFlag::QUIT]) {
        return STAGE_MAP[STAGE_ID::QUIT];
    }
    if (key_state[utl::KeyFlag::K_ESCAPE] || key_state[utl::KeyFlag::K_ENTER]) {
        return STAGE_MAP[STAGE_ID::TITLE_SCREEN];
    }

    if (key_state[utl::KeyFlag::WINDOW_CHANGE]) {
        reset_title(m_GameOverText);
        reset_score(m_ScoreText);

        for (auto& physEnt : m_physMan.physEntities) {
            physEnt->updateScreen(m_gameWorld.screen);
        }
    }

    return STAGE_MAP[STAGE_ID::GAME_OVER];
}

void GameOver::check_asteroids_cleared()
{
    asteroidsRemain = m_physMan.do_entities_remain_of_type(
            ENTITY_FLAG::ASTEROID, m_physMan.physEntities);
}

void GameOver::stop_enemy_firing()
{
    if (!asteroidsRemain) {
       for (auto& ent : m_physMan.physEntities) {
            if (ent->type() == ENTITY_MAP[ENTITY_FLAG::ENEMY]) {
                Enemy* eptr{static_cast<Enemy*>(ent.get())};
                eptr->clearedScreen();
            }
        }
    }
}

static void update_physics(const double& dt,
        std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities)
{
    for (auto& physEnt : physEntities) {
            physEnt->physicsComponent.update(dt);
    }
}

static void update_entities(const double& t, const double& dt,
            std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities)
{
    for (auto& physEnt : physEntities) {
        physEnt->update(t, dt);
    }

}

std::string GameOver::update(double t, double dt)
{
    check_asteroids_cleared();
    stop_enemy_firing();

    update_physics(dt, m_physMan.physEntities);
    update_entities(t, dt, m_physMan.physEntities);

    m_physMan.check_bullet_hits(true);
    m_physMan.clean_up(m_scoreMan, true);

    return STAGE_MAP[STAGE_ID::GAME_OVER];
}

static void render_entities(std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
        utl::Renderer& renderer)
{
    for (auto& physEntity : physEntities) {
        physEntity->render(renderer);
    }
}

void GameOver::render(double, double)
{
    utl::clearScreen(renderer());
    render_entities(m_physMan.physEntities, renderer());
    m_GameOverText.render(renderer());
    m_ScoreText.render(renderer());
    utl::presentRenderer(renderer());
}
