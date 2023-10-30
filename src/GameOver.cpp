#include "../inc/GameOver.hpp"

#include <array>
#include <memory>
#include <random>
#include <string>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Stage.hpp"
#include "../inc/TextObject.hpp"
#include "../inc/utility.hpp"

static const std::string fontPath{ "data/Play-Regular.ttf" };
static constexpr int titleFont_size{ 72 };
static constexpr int scoreFont_size{ 48 };

GameOver::GameOver(Box screen, Uint32 windowID, SDL_Renderer* rend,
                   std::vector<std::unique_ptr<PhysicsEntity>>& physEntities,
             int score)
    : Stage{ screen, windowID, rend, StageID::HIGH_SCORES },
      m_gameWorld{ screen },
      m_titleFont{ utl::createFont(fontPath, titleFont_size) },
      m_scoreFont{ utl::createFont(fontPath, scoreFont_size) },
      m_rng{ utl::makeSeededRNG() },
      m_physMan{ m_gameWorld, m_rng }, m_scoreMan{ }, m_score{ score },
      m_GameOverText{ m_gameWorld, {}, m_titleFont.get(),
          customCols::text_col, rend },
      m_ScoreText{ m_gameWorld, {}, m_scoreFont.get(),
    customCols::text_col, rend }
{
    constexpr double padding{ 250.0 };

    // remove Player from m_physMan
    m_physMan.physEntities.erase(m_physMan.physEntities.begin());

    for (auto& pE : physEntities) {
        if (pE->type != EntityFlag::PLAYER)
            m_physMan.physEntities.push_back(std::move(pE));
    }

    m_GameOverText.updateText("Game Over", renderer());
    double titleXPos = screen.w / 2.0 - m_GameOverText.size().x / 2.0;
    double titleYPos = screen.h / 3.0;
    m_GameOverText.setPos({titleXPos, titleYPos});

    m_ScoreText.updateText("Score: " + std::to_string(m_score), renderer());
    double scoreXPos = screen.w / 2.0 - m_ScoreText.size().x / 2.0;
    double scoreYPos = screen.h - padding - m_ScoreText.size().y;
    m_ScoreText.setPos({scoreXPos, scoreYPos});
}

StageID GameOver::handle_input(double, double,
    std::array<bool, KeyFlag::K_TOTAL> &key_state)
{
    GameLoop::process_input(m_gameWorld, windowID(), key_state);

    if(key_state[KeyFlag::QUIT])
        return StageID::QUIT;
    if (key_state[KeyFlag::K_ESCAPE] || key_state[KeyFlag::K_ENTER])
        return StageID::TITLE_SCREEN;

    return StageID::HIGH_SCORES;
}

StageID GameOver::update(double t, double dt)
{
    for (auto& physComp : m_physMan.physEntities) {
        physComp->physicsComponent.update(dt);
    }
    for (auto& physEnt : m_physMan.physEntities) {
        physEnt->update(t, dt);
    }

    m_physMan.checkBulletsHit();
    m_physMan.clean_up(m_scoreMan);

    return StageID::HIGH_SCORES;
}

void GameOver::render(double, double)
{
    SDL_RenderClear(renderer());
    for (auto& physEntity : m_physMan.physEntities){
        physEntity->render(renderer());
    }
    m_GameOverText.render(renderer());
    m_ScoreText.render(renderer());
    SDL_RenderPresent(renderer());
}
