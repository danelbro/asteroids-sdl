#include "../inc/utility.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Vec2d.hpp"

std::ofstream errorLogger("exception.log");

namespace utl {
    SdlException::SdlException(std::string message)
        : std::runtime_error{ message }
    {}

    void init(Uint32 sdlFlags)
    {
        if (SDL_Init(sdlFlags) != 0)
            throw SdlException(
                std::string{ "Cannot initialise SDL! SDL_Error: ",
                SDL_GetError() });

        if (TTF_Init() == -1)
            throw SdlException(
                std::string{ "Cannot initialise SDL_TTF! TTF_Error: ",
                TTF_GetError() });
    }

    SDL_Window* createWindow(const char* title, int x, int y,
        int w, int h, Uint32 flags)
    {
#ifdef _DEBUG
        errorLogger << "creating a window\n";
#endif
        SDL_Window* window = nullptr;

        window = SDL_CreateWindow(title, x, y, w, h, flags);

        if (!window)
            throw SdlException(
                std::string{ "Cannot create window! SDL_Error: ",
                SDL_GetError() });

        return window;
    }

    SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags)
    {
#ifdef _DEBUG
        errorLogger << "creating a renderer\n";
#endif
        SDL_Renderer* rend = nullptr;
        rend = SDL_CreateRenderer(window, index, flags);

        if (!rend)
            throw SdlException(
                std::string{ "Cannot create renderer! SDL_Error: ",
                SDL_GetError() });

        return rend;
    }

    textStruct createTextTexture(TTF_Font* font, std::string text,
        SDL_Color text_colour, SDL_Renderer* rend)
    {
#ifdef _DEBUG
        errorLogger << "creating a text texture\n";
#endif
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(),
            text_colour);

        if (!textSurface)
            throw SdlException(std::string{
            "Could not create textSurface! SDL_Error: ", SDL_GetError() });
        else
        {
            auto texP = SDL_CreateTextureFromSurface(rend, textSurface);
            if (!texP)
                throw SdlException(std::string{
                "Could not create texture from textSurface! SDL_Error: ",
                SDL_GetError() });
            else
            {
                auto w{textSurface->w};
                auto h{textSurface->h};
                SDL_FreeSurface(textSurface);
                textSurface = nullptr;

                return textStruct{texP, w, h};
            }
        }
    }

    std::unique_ptr<TTF_Font, sdl_deleter> createFont(std::string path,
        int font_size)
    {
#ifdef _DEBUG
        errorLogger << "creating a font\n";
#endif
        return std::unique_ptr<TTF_Font, sdl_deleter>(
            TTF_OpenFont(path.c_str(), font_size),
            sdl_deleter());
    }


    Vec2d randomPos(std::mt19937& rng, int w, int h)
    {
        std::uniform_real_distribution<double> xDist(0.0,
                                                     static_cast<double>(w));
        std::uniform_real_distribution<double> yDist(0.0,
                                                     static_cast<double>(h));

        return {xDist(rng), yDist(rng)};
    }
}
