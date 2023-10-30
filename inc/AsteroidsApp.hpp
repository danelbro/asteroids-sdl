#pragma once

#include <memory>
#include <string>

#include <SDL.h>

#include "Application.hpp"
#include "Box.hpp"
#include "FlagEnums.hpp"
#include "StageManager.hpp"
#include "utility.hpp"

class AsteroidsApp : public Application
{
public:
    AsteroidsApp();
    void run() override;
private:
    const std::string m_title;
    const int m_screenWidth;
    const int m_screenHeight;
    const Box m_screen;
    const Uint32 m_windowFlags;
    const std::unique_ptr<SDL_Window, utl::sdl_deleter> m_window;
    const Uint32 m_windowID;
    const Uint32 m_rendererFlags;
    const std::unique_ptr<SDL_Renderer, utl::sdl_deleter> m_renderer;
    const StageID m_first_stage;
    StageManager m_stageMan;
};
