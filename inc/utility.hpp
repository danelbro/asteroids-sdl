#pragma once

#include <fstream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

struct Vec2d;

extern std::ofstream errorLogger;

namespace utl {

    // thanks to https://stackoverflow.com/a/24252225
    struct sdl_deleter
    {
        void operator()(SDL_Window* w) const {
#ifdef _DEBUG
            errorLogger << "destroying a window\n";
#endif
            SDL_DestroyWindow(w);
        }
        void operator()(SDL_Renderer* r) const {
#ifdef _DEBUG
            errorLogger << "destroying a renderer\n";
#endif
            SDL_DestroyRenderer(r);
        }
        void operator()(SDL_Surface* s) const {
#ifdef _DEBUG
            errorLogger << "freeing a surface\n";
#endif
            SDL_FreeSurface(s);
        }
        void operator()(SDL_Texture* t) const {
#ifdef _DEBUG
            errorLogger << "destroying a texture\n";
#endif
            SDL_DestroyTexture(t);
        }
        void operator()(TTF_Font* f) {
#ifdef _DEBUG
            errorLogger << "closing a font\n";
#endif
            TTF_CloseFont(f);
        }
    };

    // wrapper around std::runtime_error to make SDL exception handling
    // smoother
    class SdlException : public std::runtime_error
    {
    public:
        SdlException(std::string e);
    };

    // Initialise SDL with sdlFlags.
    // Throw SdlException if initialisation fails
    void init(Uint32 sdlFlags);

    // Create an SDL_Window*. Throw an SdlException if creation fails
    std::unique_ptr<SDL_Window, sdl_deleter> createWindow(const char* title,
                                                          int x, int y,
                                                          int w, int h,
                                                          Uint32 flags);

    // Create an SDL_Renderer*. Throw an SdlException if creation fails
    std::unique_ptr<SDL_Renderer, sdl_deleter> createRenderer(
        SDL_Window* window, int index, Uint32 flags);

    struct textStruct
    {
        textStruct(std::unique_ptr<SDL_Texture, sdl_deleter> newTexP,
                   int newW, int newH);

        std::unique_ptr<SDL_Texture, sdl_deleter> texP;
        int w;
        int h;
    };

    // Create an SDL_Texture* rendered from text.
    // Throw an SdlException if creation fails
    textStruct createTextTexture(TTF_Font* font, std::string text,
        SDL_Color text_colour, SDL_Renderer* rend);

   std::unique_ptr<TTF_Font, sdl_deleter> createFont(std::string path,
       int font_size);

    Vec2d randomPos(std::mt19937& rng, int w, int h);

    std::mt19937 makeSeededRNG();
}
