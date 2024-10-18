#include "HighScores.hpp"

#include "Colors.hpp"
#include "Enemy.hpp"
#include "flags.hpp"

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <utl_Box.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_ScoreBoard.hpp>
#include <utl_Stage.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_utility.hpp>
#include <vector>

static const std::string fontPath{"data/Play-Regular.ttf"};
static constexpr int titleFont_size{64};
static constexpr int scoreFont_size{36};
static constexpr double padding{250.0};
static const std::string highScoresPath{"data/highScores"};

HighScores::HighScores(
    utl::Box& screen, uint32_t windowID, utl::Renderer& renderer,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
    int score)
    : utl::Stage{screen, windowID, renderer, STAGE_MAP[STAGE_ID::HIGH_SCORES]},
      m_gameWorld{screen, 0.1},
      titleFont{utl::createFont(fontPath, titleFont_size)},
      scoreFont{utl::createFont(fontPath, scoreFont_size)},
      m_rng{utl::makeSeededRNG()}, m_physMan{m_gameWorld, m_rng},
      m_scoreMan{renderer}, m_score{score},
      m_highScoreTitle{
          m_gameWorld.screen, {}, titleFont, customCols::text_col, renderer},
      asteroidsRemain{false},
      m_scoreBoard{screen, {}, scoreFont, customCols::text_col, renderer}
{
    for (size_t i{0}; i < m_physMan.physEntities.size(); i++) {
        if (ENTITY_STRING_MAP[m_physMan.physEntities[i]->type()]
            == ENTITY_FLAG::PLAYER) {
            m_physMan.physEntities.erase(m_physMan.physEntities.begin()
                                         + static_cast<unsigned>(i));
        }
    }

    for (auto& physEnt : physEntities) {
        switch (ENTITY_STRING_MAP[physEnt->type()]) {
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
    }
    m_highScoreTitle.updateText("High Scores");
    const double titleXPos{screen.w / 2.0 - m_highScoreTitle.size().x / 2.0};
    const double titleYPos{screen.h / 3.0};
    m_highScoreTitle.setPos({titleXPos, titleYPos});

    std::vector<std::string> highScores{};
    read_high_scores(highScores, highScoresPath);
    calculate_high_scores(score, highScores);
    write_high_scores(highScores, highScoresPath);

    m_scoreBoard.set_text(highScores);
    const double scoreBoardXPos{};
    const double scoreBoardYPos{};
    m_scoreBoard.set_pos(scoreBoardXPos, scoreBoardYPos);

    check_asteroids_cleared();
}

static void reset_title(utl::TextObject& title)
{
    title.setPos({title.screen().w / 2.0 - title.size().x / 2.0,
                  title.screen().h / 3.0});
}

std::string
HighScores::handle_input(double, double,
                         std::array<bool, utl::KeyFlag::K_TOTAL>& keyState)
{
    utl::process_input(screen(), windowID(), keyState);

    if (keyState[utl::KeyFlag::WINDOW_CHANGE]) {
        m_gameWorld.screen = screen();
        reset_title(m_highScoreTitle);

        for (auto& physEnt : m_physMan.physEntities) {
            physEnt->updateScreen(m_gameWorld.screen);
        }
    }

    if (keyState[utl::KeyFlag::QUIT]) {
        return STAGE_MAP[STAGE_ID::QUIT];
    }
    if (keyState[utl::KeyFlag::K_ENTER] || keyState[utl::KeyFlag::K_ESCAPE]) {
        return STAGE_MAP[STAGE_ID::TITLE_SCREEN];
    }

    return STAGE_MAP[STAGE_ID::HIGH_SCORES];
}

void HighScores::stop_enemy_firing()
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

std::string HighScores::update(double t, double dt)
{
    check_asteroids_cleared();
    stop_enemy_firing();

    update_physics(dt, m_physMan.physEntities);
    update_entities(t, dt, m_physMan.physEntities);

    m_physMan.check_bullet_hits(true);
    m_physMan.clean_up(m_scoreMan, true);

    return STAGE_MAP[STAGE_ID::HIGH_SCORES];
}

static void render_entities(
    std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
    utl::Renderer& renderer)
{
    for (auto& physEntity : physEntities) {
        physEntity->render(renderer);
    }
}

void HighScores::render(double, double)
{
    utl::clearScreen(renderer());
    render_entities(m_physMan.physEntities, renderer());
    m_highScoreTitle.render(renderer());
    utl::presentRenderer(renderer());
}

void HighScores::check_asteroids_cleared()
{
    asteroidsRemain = m_physMan.do_entities_remain_of_type(
        ENTITY_FLAG::ASTEROID, m_physMan.physEntities);
}

void HighScores::read_high_scores(std::vector<std::string>&, const std::string&)
{}
void HighScores::calculate_high_scores(const int&, std::vector<std::string>&) {}
void HighScores::write_high_scores(const std::vector<std::string>&,
                                   const std::string&)
{}
