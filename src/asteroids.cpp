// Plays a game of asteroids
#include <exception>
#include <stdexcept>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>

#include "AsteroidsApp.hpp"
#include "utility.hpp"

#ifdef _WIN32
int WinMain()
#elif __linux__
int main()
#endif
try
{
    constexpr auto sdlFlags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
    utl::init(sdlFlags);

    {
        AsteroidsApp asteroids{};
        asteroids.run();
    }

    utl::quit_sdl();

    return 0;
}
catch (utl::SdlException& se)
{
    utl::errorLogger << "SDL exception: " << se.what() << '\n';
    utl::quit_sdl();
    return 1;
}
catch (std::runtime_error &re)
{
    utl::errorLogger << "exception: " << re.what() << '\n';
    utl::quit_sdl();
    return 2;
}
catch (std::out_of_range& oor)
{
    utl::errorLogger << "out of range: " << oor.what() << '\n';
    utl::quit_sdl();
    return 3;
}
catch (std::exception& e)
{
    utl::errorLogger << "std::exception: " << e.what() << '\n';
    utl::quit_sdl();
    return 4;
}
catch (...)
{
    utl::errorLogger << "unknown exception\n";
    utl::quit_sdl();
    return -1;
}
