// Plays an asteroids game
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Box.hpp"
#include "../inc/Colors.hpp"
#include "../inc/MainLevel.hpp"
#include "../inc/StageManager.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

std::ofstream errorLogger("exception.log");

#ifdef _WIN32
int WinMain()
#elif __linux__
int main()
#endif
try
{
    constexpr auto sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    utl::init(sdlFlags);

    // Window initialisation
    std::string title = "Asteroids";

    constexpr int screenWidth{ 960 };
    constexpr int screenHeight{ 720 };

    constexpr Box screen{ screenWidth, screenHeight };

    constexpr auto windowFlags = SDL_WindowFlags::SDL_WINDOW_RESIZABLE;

    auto window = std::unique_ptr<SDL_Window, utl::sdl_deleter>{
        utl::createWindow(title.c_str(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screen.w, screen.h, windowFlags) };

    auto windowID = SDL_GetWindowID(window.get());

    // Renderer intialisation
    constexpr auto rendererFlags = 
        SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC;

    auto renderer = std::unique_ptr<SDL_Renderer, utl::sdl_deleter>{
        utl::createRenderer(window.get(), -1, rendererFlags) };

    {
        StageManager stageMan{};

        // stageMan.add_stage(StageID::TITLE_SCREEN,
        //     std::make_unique<TitleScreen>(
        // screen, windowID, renderer.get()));

        stageMan.add_stage(StageID::PLAYING,
            std::make_unique<MainLevel>(screen, windowID, renderer.get()));

        stageMan.run();
    }

    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());

    TTF_Quit();
    SDL_Quit();
    return 0;
}
catch (utl::SdlException& se)
{
    errorLogger << "SDL exception: " << se.what() << '\n';
    return 1;
}
catch (std::runtime_error &e)
{
    errorLogger << "exception: " << e.what() << '\n';
    return 2;
}
catch (...)
{
    errorLogger << "unknown exception\n";
    return -1;
}
