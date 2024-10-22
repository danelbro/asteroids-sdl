#include "GameOver.hpp"

#include "Colors.hpp"
#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "constants.hpp"
#include "flags.hpp"

#include <array>
#include <filesystem>
#include <memory>
#include <string>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_utility.hpp>

static void reset_text_positions(utl::TextObject& title,
                                 utl::TextObject& score);
static void reset_title(utl::TextObject& title);
static void reset_score(utl::TextObject& score);

GameOver::GameOver(
    utl::Box& screen, uint32_t windowID, utl::Renderer& rend,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
    int score)
    : Stage{screen, windowID, rend, STAGE_MAP[STAGE_ID::GAME_OVER]},
      m_gameWorld{screen, constants::fluidDensity},
      m_titleFont{utl::createFont(constants::fontPath,
                                  constants::gameOverTitleFontSize)},
      m_scoreFont{utl::createFont(constants::fontPath,
                                  constants::gameOverScoreFontSize)},
      m_rng{utl::makeSeededRNG()}, m_physMan{m_gameWorld, m_rng},
      m_scoreMan{rend}, m_score{score},
      m_GameOverText{
          m_gameWorld.screen, {}, m_titleFont, customCols::text_col, rend},
      m_ScoreText{
          m_gameWorld.screen, {}, m_scoreFont, customCols::text_col, rend},
      asteroidsRemain{false}
{
    for (size_t i{0}; i < m_physMan.physEntities.size(); i++) {
        if (ENTITY_STRING_MAP[m_physMan.physEntities[i]->type()]
            == ENTITY_FLAG::PLAYER) {
            m_physMan.physEntities.erase(m_physMan.physEntities.begin()
                                         + static_cast<unsigned>(i));
        }
    }

    // for (auto& physEnt : physEntities) {
    for (size_t i{0}; i < physEntities.size(); i++) {
        switch (ENTITY_STRING_MAP[physEntities[i]->type()]) {
        case ENTITY_FLAG::PLAYER:
            break;
        case ENTITY_FLAG::ASTEROID:
            m_physMan.make_asteroid(*physEntities[i]);
            break;
        case ENTITY_FLAG::BULLET:
        case ENTITY_FLAG::ENEMY_BULLET:
            m_physMan.make_bullet(*physEntities[i]);
            break;
        case ENTITY_FLAG::ENEMY:
            m_physMan.make_enemy(*physEntities[i]);
            break;
        default:
            break;
        }

        check_asteroids_cleared();
    }

    m_GameOverText.updateText("Game Over");
    m_ScoreText.updateText("Score: " + std::to_string(m_score));
    reset_text_positions(m_GameOverText, m_ScoreText);

    m_scoreMan.score = m_score;
}

static void reset_text_positions(utl::TextObject& title, utl::TextObject& score)
{
    reset_title(title);
    reset_score(score);
}

static void reset_title(utl::TextObject& title)
{
    const double titleXPos{title.screen().w / 2.0 - title.size().x / 2.0};
    const double titleYPos{title.screen().h / 3.0};
    title.setPos({titleXPos, titleYPos});
}

static void reset_score(utl::TextObject& score)
{
    const double scoreXPos{score.screen().w / 2.0 - score.size().x / 2.0};
    const double scoreYPos{score.screen().h - constants::gameOverPadding
                           - score.size().y};
    score.setPos({scoreXPos, scoreYPos});
}

std::string
GameOver::handle_input(double, double,
                       std::array<bool, utl::KeyFlag::K_TOTAL>& keyState)
{
    utl::process_input(screen(), windowID(), keyState);

    if (keyState[utl::KeyFlag::WINDOW_CHANGE]) {
        m_gameWorld.screen = screen();
        for (auto& physEnt : m_physMan.physEntities) {
            physEnt->updateScreen(m_gameWorld.screen);
        }

        reset_text_positions(m_GameOverText, m_ScoreText);
    }

    if (keyState[utl::KeyFlag::QUIT]) {
        return STAGE_MAP[STAGE_ID::QUIT];
    }
    if (keyState[utl::KeyFlag::K_ESCAPE] || keyState[utl::KeyFlag::K_ENTER]) {
        return STAGE_MAP[STAGE_ID::HIGH_SCORES];
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

static void
update_physics(const double& dt,
               std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities)
{
    for (auto& physEnt : physEntities) {
        physEnt->physicsComponent.update(dt);
    }
}

static void update_entities(
    const double& t, const double& dt,
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

static void render_entities(
    std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
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
