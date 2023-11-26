#include "AsteroidsApp.hpp"

#include <cstdint>
#include <memory>
#include <string>

#include "Application.hpp"
#include "Box.hpp"
#include "StageManager.hpp"
#include "TitleScreen.hpp"
#include "utility.hpp"

AsteroidsApp::AsteroidsApp(const std::string& title, int screenWidth,
                           int screenHeight, uint32_t windowFlags,
                           uint32_t renderFlags)
    : Application{},
      m_title{ title }, m_screenWidth{ screenWidth },
      m_screenHeight{ screenHeight },
      m_screen{ m_screenWidth, m_screenHeight },
      m_windowFlags{ windowFlags },
      m_window{ utl::createWindow(m_title.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  m_screen.w, m_screen.h, m_windowFlags) },
      m_windowID{ m_window.ID() },
      m_rendererFlags{ renderFlags },
      m_renderer{ utl::createRenderer(m_window, -1, m_rendererFlags) },
      m_first_stage{ utl::StageID::TITLE_SCREEN }, m_stageMan{ m_first_stage }
{
    m_stageMan.add_stage(m_first_stage,
        std::make_unique<TitleScreen>(m_screen, m_windowID,
                                      m_renderer));
}

void AsteroidsApp::run()
{
    m_stageMan.run();
}
