#pragma once

#include <cstdint>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include "utility.hpp"

namespace utl {
    // Custom deleters for SDL types. Pass when constructing a unique_ptr
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
        SdlException(const std::string& e);
    };

    // Initialise SDL with sdlFlags.
    // Throw SdlException if initialisation fails
    void init(uint32_t sdlFlags);

    // Run SDL and TTF quit functions
    void quit_sdl();

    using WindowPtr = std::unique_ptr<SDL_Window, sdl_deleter>;
    using RendererPtr = std::unique_ptr<SDL_Renderer, sdl_deleter>;
    using SurfacePtr = std::unique_ptr<SDL_Surface, sdl_deleter>;
    using TexturePtr = std::unique_ptr<SDL_Texture, sdl_deleter>;
    using FontPtr = std::unique_ptr<TTF_Font, sdl_deleter>;

    // Create an SDL_Window*. Throw an SdlException if creation fails
    WindowPtr createWindow(const std::string& title, int x, int y,
                           int w, int h, uint32_t flags);

    // Create an SDL_Renderer*. Throw an SdlException if creation fails
    RendererPtr createRenderer(SDL_Window* window, int index, uint32_t flags);

    struct textStruct
    {
        textStruct(TexturePtr newTexP, int newW, int newH);

        TexturePtr texP;
        int w;
        int h;
    };

    // Create an SDL_Texture* rendered from text.
    // Throw an SdlException if creation fails
    textStruct createTextTexture(TTF_Font* font, const std::string& text,
        SDL_Color text_colour, SDL_Renderer* rend);

    // Create a TTF_Font. Throw an SdlException if creation fails
    FontPtr createFont(const std::string& path, int font_size);
} // namespace utl
