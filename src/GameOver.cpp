#include "GameOver.hpp"

#include <array>
#include <memory>
#include <string>

#include "Colors.hpp"
#include "Enemy.hpp"
#include "flags.hpp"
#include "SDL_Interface.hpp"
#include "GameWorld.hpp"
#include "PhysicsEntity.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

static const std::string fontPath{ "data/Play-Regular.ttf" };
static constexpr int titleFont_size{ 72 };
static constexpr int scoreFont_size{ 48 };
static constexpr double padding{ 250.0 };

GameOver::GameOver(const Box& screen, uint32_t windowID, utl::Renderer& rend,
                   const std::vector<std::unique_ptr<PhysicsEntity>>& physEntities,
                   int score)
: Stage{ screen, windowID, rend, utl::stageMap[utl::StageID::GAME_OVER] },
m_gameWorld{ screen, 0.1 },
m_titleFont{ utl::createFont(fontPath, titleFont_size) },
m_scoreFont{ utl::createFont(fontPath, scoreFont_size) },
m_rng{ utl::makeSeededRNG() }, m_physMan{ m_gameWorld, m_rng },
m_scoreMan{ rend }, m_score{ score },
m_GameOverText{
    m_gameWorld, {}, m_titleFont, utl::customCols::text_col, rend
},
m_ScoreText{
    m_gameWorld, {}, m_scoreFont, utl::customCols::text_col, rend
}
{
    // remove Player from m_physMan
    m_physMan.physEntities.erase(m_physMan.physEntities.begin());

    for (auto& pE : physEntities) {
        switch (utl::entityStringMap[pE->type()])
        {
        case utl::EntityFlag::PLAYER:
            break;
        case utl::EntityFlag::ASTEROID:
            m_physMan.make_asteroid(*pE);
            break;
        case utl::EntityFlag::BULLET: case utl::EntityFlag::ENEMY_BULLET:
            m_physMan.make_bullet(*pE);
            break;
        case utl::EntityFlag::ENEMY:
            m_physMan.make_enemy(*pE);
            break;
        default:
            break;
        }
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

static void reset_title(TextObject& title)
{
    title.setPos({
            title.gameWorld.screen.w / 2.0 - title.size().x / 2.0,
            title.gameWorld.screen.h / 3.0
        });
}

static void reset_score(TextObject& score)
{
    score.setPos({
            score.gameWorld.screen.w / 2.0 - score.size().x / 2.0,
            score.gameWorld.screen.h - padding - score.size().y
        });
}

std::string GameOver::handle_input(double, double,
    std::array<bool, utl::KeyFlag::K_TOTAL> &key_state)
{
    utl::process_input(m_gameWorld, windowID(), key_state);

    if(key_state[utl::KeyFlag::QUIT])
        return utl::stageMap[utl::StageID::QUIT];
    if (key_state[utl::KeyFlag::K_ESCAPE] || key_state[utl::KeyFlag::K_ENTER])
        return utl::stageMap[utl::StageID::TITLE_SCREEN];

    if (key_state[utl::KeyFlag::WINDOW_CHANGE])
    {
        reset_title(m_GameOverText);
        reset_score(m_ScoreText);

        for (auto& pE : m_physMan.physEntities) {
            pE->gameWorld.screen = m_gameWorld.screen;
        }
    }

    return utl::stageMap[utl::StageID::GAME_OVER];
}

std::string GameOver::update(double t, double dt)
 {
    bool asteroidsRemain{ false };
    for (auto& ent : m_physMan.physEntities) {
        if (ent->type() == utl::entityMap[utl::EntityFlag::ASTEROID]) {
            asteroidsRemain = true;
            break;
        }
    }

    if (!asteroidsRemain) {
        for (auto& ent : m_physMan.physEntities) {
            if (ent->type() == utl::entityMap[utl::EntityFlag::ENEMY]) {
                Enemy* eptr{ static_cast<Enemy*>(ent.get()) };
                eptr->clearedScreen();
            }
        }
     }

    for (auto& physEnt : m_physMan.physEntities) {
        physEnt->physicsComponent.update(dt);
    }
    for (auto& physEnt : m_physMan.physEntities) {
        physEnt->update(t, dt);
    }

    m_physMan.checkBulletsHit(true);
    m_physMan.clean_up(m_scoreMan, true);

    return utl::stageMap[utl::StageID::GAME_OVER];
}

void GameOver::render(double, double)
{
    utl::Renderer& rend{ renderer() };
    utl::clearScreen(rend);
    for (auto& physEntity : m_physMan.physEntities){
        physEntity->render(rend);
    }
    m_GameOverText.render(rend);
    m_ScoreText.render(rend);
    utl::presentRenderer(rend);
}
