// Plays a game of asteroids

#include "AsteroidsApp.hpp"

#include <SDL3/SDL_main.h>
#include <stdexcept>
#include <utl_SDLInterface.hpp>
#include <utl_utility.hpp>

int main()
try {
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
catch (utl::SdlException& se) {
    utl::errorLogger << "SDL exception: " << se.what() << '\n';
    utl::quit_sdl();
    return 1;
}
catch (std::runtime_error& re) {
    utl::errorLogger << "exception: " << re.what() << '\n';
    utl::quit_sdl();
    return 2;
}
catch (std::out_of_range& oor) {
    utl::errorLogger << "out of range: " << oor.what() << '\n';
    utl::quit_sdl();
    return 3;
}
catch (...) {
    utl::errorLogger << "unknown exception\n";
    utl::quit_sdl();
    return -1;
}
