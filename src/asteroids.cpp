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
    constexpr unsigned sdlFlags = SDL_INIT_VIDEO;
    init(sdlFlags);

    // Window initialisation
    std::unique_ptr<SDL_Window, SDL_WindowDestroyer> window{ nullptr };
    char title[] = "Asteroids";
    const Box screen{ 960, 720 };
    constexpr unsigned windowFlags = SDL_WINDOW_RESIZABLE;
    window = std::unique_ptr<SDL_Window, SDL_WindowDestroyer>{
        createWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     screen.w, screen.h, windowFlags) };
    auto windowID = SDL_GetWindowID(window.get());

    // Renderer intialisation
    std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer> renderer{ nullptr };
    constexpr int rendererFlags = SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC;
    renderer = std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer>{
        createRenderer(window.get(), -1, rendererFlags) };

    SDL_SetRenderDrawColor(renderer.get(), customCols::bg.r, customCols::bg.g,
        customCols::bg.b, customCols::bg.a);

    StageManager stageMan{};
    stageMan.add_stage(StageID::PLAYING,
                       new MainLevel{screen, windowID, renderer.get()});

    stageMan.run();

    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());

    TTF_Quit();
    SDL_Quit();
    return 0;
}
catch (std::exception &e)
{
    errorLogger << "exception: " << e.what() << '\n';
    return 1;
}
catch (...)
{
    errorLogger << "unknown exception\n";
    return 2;
}
