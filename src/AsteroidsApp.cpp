#include "AsteroidsApp.hpp"

#include "GameOver.hpp"
#include "HighScores.hpp"
#include "MainLevel.hpp"
#include "TitleScreen.hpp"
#include "flags.hpp"

#include <cstdint>
#include <string>
#include <utl_Application.hpp>
#include <utl_Box.hpp>
#include <utl_StageManager.hpp>
#include <utl_utility.hpp>

AsteroidsApp::AsteroidsApp(const std::string& title, int screenWidth,
                           int screenHeight, uint32_t windowFlags)
    : Application{title, screenWidth, screenHeight, windowFlags}
{
    m_renderer.setVSync(1);

    m_stageManager.add_stage<TitleScreen>(STAGE_MAP.at(STAGE_ID::TITLE_SCREEN),
                                          m_screenSpace, m_windowID,
                                          m_renderer);
    m_stageManager.set_current_stage(STAGE_MAP.at(STAGE_ID::TITLE_SCREEN));
    m_stageManager.set_next_stage(STAGE_MAP.at(STAGE_ID::TITLE_SCREEN));

    LOG("Constructed AsteroidsApp\n");
}

void AsteroidsApp::trigger_stage_change(const std::string& next)
{
    utl::Box& screen{m_stageManager.get_current_stage()->screen()};
    uint32_t windowID{m_stageManager.get_current_stage()->windowID()};
    utl::Renderer& renderer{m_stageManager.get_current_stage()->renderer()};

    switch (STAGE_STRING_MAP.at(next)) {
    case STAGE_ID::TITLE_SCREEN:
        m_stageManager.add_stage<TitleScreen>(next, screen, windowID, renderer);
        break;
    case STAGE_ID::PLAYING:
        m_stageManager.add_stage<MainLevel>(next, screen, windowID, renderer);
        break;
    case STAGE_ID::GAME_OVER: {
        MainLevel* mlptr{nullptr};

        if (m_stageManager.get_current() != STAGE_MAP.at(STAGE_ID::PLAYING)) {
            throw std::runtime_error(
                "Trying to enter game over screen without playing!\n");
        }

        mlptr = static_cast<MainLevel*>(m_stageManager.get_current_stage());

        m_stageManager.add_stage<GameOver>(next, screen, windowID, renderer,
                                           mlptr->physMan().physEntities,
                                           mlptr->scoreMan().score);

        break;
    }
    case STAGE_ID::HIGH_SCORES: {
        GameOver* goptr{nullptr};

        if (m_stageManager.get_current() != STAGE_MAP.at(STAGE_ID::GAME_OVER)) {
            throw std::runtime_error(
                "Trying to enter highscores screen before game over!\n");
        }

        goptr = static_cast<GameOver*>(m_stageManager.get_current_stage());

        m_stageManager.add_stage<HighScores>(next, screen, windowID, renderer,
                                             goptr->physMan().physEntities,
                                             goptr->scoreMan().score);
        break;
    }
    case STAGE_ID::QUIT:
        break;
    default:
        throw std::runtime_error("bad stage!\n");
    }

    LOG("Going to " << next << " stage\n");
}
