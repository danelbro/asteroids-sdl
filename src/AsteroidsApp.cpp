#include "../inc/AsteroidsApp.hpp"

#include <memory>
#include <string>

#include <SDL.h>

#include "../inc/Box.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/StageManager.hpp"
#include "../inc/utility.hpp"

AsteroidsApp::AsteroidsApp()
    : Application{},
      m_title{ "Asteroids" }, m_screenWidth{ 960 }, m_screenHeight{ 720 },
      m_screen{ m_screenWidth, m_screenHeight },
      m_windowFlags{ SDL_WindowFlags::SDL_WINDOW_RESIZABLE },
      m_window{ utl::createWindow(m_title.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  m_screen.w, m_screen.h, m_windowFlags) },
      m_windowID{ SDL_GetWindowID(m_window.get()) },
      m_rendererFlags{ SDL_RendererFlags::SDL_RENDERER_ACCELERATED |
                       SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC },
      m_renderer{ utl::createRenderer(m_window.get(), -1, m_rendererFlags) },
      m_first_stage{ StageID::TITLE_SCREEN }, m_stageMan{ m_first_stage }
{
    m_stageMan.add_stage(m_first_stage,
                         std::make_unique<TitleScreen>(m_screen, m_windowID,
                                                       m_renderer.get()));
}

void AsteroidsApp::run()
{
    m_stageMan.run()
}
