#include "../inc/utility.hpp"

#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

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
                SDL_FreeSurface(textSurface);

                return textStruct {
                    std::unique_ptr<SDL_Texture, sdl_deleter>(texP),
                    textSurface->w,
                    textSurface->h
                };
            }
        }
    }

    TTF_Font* createFont(std::string path, int font_size)
    {
        auto font = TTF_OpenFont(path.c_str(), font_size);

        if (!font) {
            throw SdlException(std::string{ "Couldn't load font! TTF_Error:",
                                           TTF_GetError() });
        }

        return font;
    }
}