// Plays an asteroids game
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/AsteroidsApp.hpp"
#include "../inc/Box.hpp"
#include "../inc/Colors.hpp"
#include "../inc/MainLevel.hpp"
#include "../inc/StageManager.hpp"
#include "../inc/TitleScreen.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

#ifdef _WIN32
int WinMain()
#elif __linux__
int main()
#endif
try
{
    constexpr auto sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    utl::init(sdlFlags);

    AsteroidsApp asteroids{};
    asteroids.run();

    TTF_Quit();
    SDL_Quit();

    return 0;
}
catch (utl::SdlException& se)
{
    errorLogger << "SDL exception: " << se.what() << '\n';
    return 1;
}
catch (std::runtime_error &re)
{
    errorLogger << "exception: " << re.what() << '\n';
    return 2;
}
catch (std::out_of_range& oor)
{
    errorLogger << "out of range: " << oor.what() << '\n';
    return 3;
}
catch (std::exception& e)
{
    errorLogger << "std::exception: " << e.what() << '\n';
    return 4;
}
catch (...)
{
    errorLogger << "unknown exception\n";
    return -1;
}
