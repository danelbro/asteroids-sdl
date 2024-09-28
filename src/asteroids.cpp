// Plays a game of asteroids

#include <stdexcept>

#include "SDL_Interface.hpp"

#include "AsteroidsApp.hpp"
#include "utility.hpp"

#ifdef _WIN32
int WinMain()
#else
int main()
#endif
try
{
    constexpr auto sdlFlags{ SDL_INIT_VIDEO | SDL_INIT_AUDIO };
    utl::init(sdlFlags);

    {
        const std::string title{ "Asteroids" };
        constexpr int width{ 960 };
        constexpr int height{ 720 };
        constexpr uint32_t sdlWindowFlags { SDL_WINDOW_RESIZABLE };
        constexpr uint32_t sdlRenderFlags { SDL_RENDERER_ACCELERATED
                                            | SDL_RENDERER_PRESENTVSYNC };

        {
            AsteroidsApp asteroids{ title, width, height,
                                    sdlWindowFlags, sdlRenderFlags };
            asteroids.run();
        };
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
catch (...)
{
    utl::errorLogger << "unknown exception\n";
    utl::quit_sdl();
    return -1;
}
