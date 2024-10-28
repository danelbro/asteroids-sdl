// Plays a game of asteroids

#include "AsteroidsApp.hpp"

#include <SDL3/SDL_main.h>
#include <stdexcept>
#include <utl_SDLInterface.hpp>

int main(int, char**)
try {
    AsteroidsApp asteroids{};
    asteroids.run();

    return 0;
}
catch (utl::SdlException& se) {
    ERRLOG("SDL exception: %s\n", se.what());
    utl::quit_sdl();
    return 1;
}
catch (std::out_of_range& oor) {
    ERRLOG("out of range: %s\n", oor.what());
    utl::quit_sdl();
    return 2;
}
catch (std::runtime_error& re) {
    ERRLOG("exception: %s\n", re.what());
    utl::quit_sdl();
    return 3;
}
catch (...) {
    ERRLOG("unknown exception\n", NULL);
    utl::quit_sdl();
    return -1;
}
