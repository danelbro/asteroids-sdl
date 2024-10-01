#include "AsteroidsApp.hpp"

#include <cstdint>
#include <memory>
#include <string>

#include "Application.hpp"
#include "Box.hpp"
#include "flags.hpp"
#include "StageManager.hpp"
#include "TitleScreen.hpp"
#include "GameOver.hpp"
#include "MainLevel.hpp"
#include "utility.hpp"

AsteroidsApp::AsteroidsApp(const std::string& title, int screenWidth,
                           int screenHeight, uint32_t windowFlags)
    : Application{title, screenWidth, screenHeight, windowFlags}
{
    m_stageMan.add_stage(utl::stageMap[utl::StageID::TITLE_SCREEN],
        std::make_unique<TitleScreen>(m_screen, m_windowID,
                                      m_renderer));
    m_stageMan.set_current_stage(utl::stageMap[utl::StageID::TITLE_SCREEN]);
    m_stageMan.set_next_stage(utl::stageMap[utl::StageID::TITLE_SCREEN]);
}

void AsteroidsApp::trigger_stage_change(const std::string& next)
{
    Box screen{ m_stageMan.get_current_stage()->screen() };
    uint32_t windowID{ m_stageMan.get_current_stage()->windowID() };
    utl::Renderer& renderer{ m_stageMan.get_current_stage()->renderer() };

    switch (utl::stageStringMap[next]){
    case utl::StageID::TITLE_SCREEN:
        m_stageMan.add_stage(next,
            std::make_unique<TitleScreen>(screen, windowID, renderer));
        break;
    case utl::StageID::PLAYING:
        m_stageMan.add_stage(next,
            std::make_unique<MainLevel>(screen, windowID, renderer));
        break;
    case utl::StageID::GAME_OVER:
    {
        MainLevel* mlptr{ nullptr };

        if (m_stageMan.get_current() != utl::stageMap[utl::StageID::PLAYING])
            throw std::runtime_error("Trying to enter game over screen without playing!\n");

        mlptr = static_cast<MainLevel*>(m_stageMan.get_current_stage());

        m_stageMan.add_stage(next,
            std::make_unique<GameOver>(screen, windowID, renderer,
                mlptr->physMan().physEntities, mlptr->scoreMan().score));

        break;
    }
    case utl::StageID::QUIT:
        m_stageMan.add_stage(next, nullptr);
        break;
    default:
        throw std::runtime_error("bad stage!\n");
    }
}
