#pragma once

#include <cstdint>
#include <string>

#include "Application.hpp"
#include "Box.hpp"
#include "SDL_Interface.hpp"
#include "StageManager.hpp"
#include "utility.hpp"

class AsteroidsApp : public Application
{
public:
    AsteroidsApp(const std::string& title, int screenWidth, int screenHeight,
                 uint32_t windowFlags, uint32_t renderFlags);
    ~AsteroidsApp() { }
    void run() override;
private:
    const std::string m_title;
    const int m_screenWidth;
    const int m_screenHeight;
    const Box m_screen;
    const uint32_t m_windowFlags;
    utl::Window m_window;
    const uint32_t m_windowID;
    const uint32_t m_rendererFlags;
    utl::Renderer m_renderer;
    const utl::StageID m_first_stage;
    StageManager m_stageMan;
};
