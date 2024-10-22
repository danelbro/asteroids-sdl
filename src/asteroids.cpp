// Plays a game of asteroids

#include "AsteroidsApp.hpp"

#include <SDL3/SDL_main.h>
#include <stdexcept>
#include <utl_SDLInterface.hpp>

#ifndef NDEBUG
#include <utl_utility.hpp>
#endif

int main(int, char**)
#ifdef NDEBUG
{
#else
try {
#endif
    constexpr auto sdlFlags{SDL_INIT_VIDEO};
    utl::init(sdlFlags);

    {
        const std::string title{"Asteroids"};
        constexpr int width{960};
        constexpr int height{720};
        constexpr uint32_t sdlWindowFlags{SDL_WINDOW_RESIZABLE};

        {
            AsteroidsApp asteroids{title, width, height, sdlWindowFlags};
            asteroids.run();
        };
    }

    utl::quit_sdl();

    return 0;
}
#ifndef NDEBUG
catch (utl::SdlException& se)
{
    ERRLOG("SDL exception: " << se.what() << '\n');
    utl::quit_sdl();
    return 1;
}
catch (std::runtime_error& re)
{
    ERRLOG("exception: " << re.what() << '\n');
    utl::quit_sdl();
    return 2;
}
catch (std::out_of_range& oor)
{
    ERRLOG("out of range: " << oor.what() << '\n');
    utl::quit_sdl();
    return 3;
}
catch (...)
{
    ERRLOG("unknown exception\n");
    utl::quit_sdl();
    return -1;
}
#endif
