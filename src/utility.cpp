#include "../inc/utility.hpp"

#include <array>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/GameWorld.hpp"
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

    std::unique_ptr<SDL_Window, sdl_deleter> createWindow(const char* title,
                                                          int x, int y,
                                                          int w, int h,
                                                          Uint32 flags)
    {
#ifdef _DEBUG
        errorLogger << "creating a window\n";
#endif
        std::unique_ptr<SDL_Window, sdl_deleter> window{
            SDL_CreateWindow(title, x, y, w, h, flags), sdl_deleter()
        };

        if (!window)
            throw SdlException(
                std::string{ "Cannot create window! SDL_Error: ",
                SDL_GetError() });

        return window;
    }

    std::unique_ptr<SDL_Renderer, sdl_deleter> createRenderer(SDL_Window* window, int index, Uint32 flags)
    {
#ifdef _DEBUG
        errorLogger << "creating a renderer\n";
#endif
        std::unique_ptr<SDL_Renderer, sdl_deleter> rend{
            SDL_CreateRenderer(window, index, flags), sdl_deleter()
        };

        if (!rend)
            throw SdlException(
                std::string{ "Cannot create renderer! SDL_Error: ",
                SDL_GetError() });

        return rend;
    }

    textStruct::textStruct(std::unique_ptr<SDL_Texture, sdl_deleter> newTexP,
                           int newW, int newH)
        : texP{std::move(newTexP)}, w{newW}, h{newH}
        {}

    textStruct createTextTexture(TTF_Font* font, std::string text,
        SDL_Color text_colour, SDL_Renderer* rend)
    {
#ifdef _DEBUG
        errorLogger << "creating a text texture\n";
#endif
        std::unique_ptr<SDL_Surface, sdl_deleter> textSurface{
            TTF_RenderUTF8_Blended(font, text.c_str(), text_colour),
            sdl_deleter()
        };

        if (!textSurface)
            throw SdlException(std::string{
            "Could not create textSurface! SDL_Error: ", SDL_GetError() });

        std::unique_ptr<SDL_Texture, sdl_deleter> texP{
            SDL_CreateTextureFromSurface(rend, textSurface.get()),
            sdl_deleter()
        };
        if (!texP)
            throw SdlException(std::string{
                    "Could not create texture from textSurface! SDL_Error: ",
                    SDL_GetError() });

        auto w{textSurface->w};
        auto h{textSurface->h};

        return textStruct{std::move(texP), w, h};
    }

    std::unique_ptr<TTF_Font, sdl_deleter> createFont(std::string path,
        int font_size)
    {
#ifdef _DEBUG
        errorLogger << "creating a font\n";
#endif
        std::unique_ptr<TTF_Font, sdl_deleter> font{
            TTF_OpenFont(path.c_str(), font_size), sdl_deleter() };

        if (!font) throw(utl::SdlException{ "Failed to make font! TTF_Error: " });

        return font;
    }

    void process_input(GameWorld& gw, Uint32 windowID,
        std::array<bool, KeyFlag::K_TOTAL>& key_state)
    {
        SDL_Event ev{ };

        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                key_state[KeyFlag::QUIT] = true;

            else if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.windowID == windowID)
                    if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        gw.screen.w = ev.window.data1;
                        gw.screen.h = ev.window.data2;
                    }
            }

            else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key_state[KeyFlag::K_ESCAPE] = true;
                    break;
                case SDLK_LEFT:
                    key_state[KeyFlag::K_LEFT] = true;
                    break;
                case SDLK_RIGHT:
                    key_state[KeyFlag::K_RIGHT] = true;
                    break;
                case SDLK_UP:
                    key_state[KeyFlag::K_UP] = true;
                    break;
                case SDLK_DOWN:
                    key_state[KeyFlag::K_DOWN] = true;
                    break;
                case SDLK_SPACE:
                    key_state[KeyFlag::K_SPACE] = true;
                    break;
                case SDLK_RETURN:
                    key_state[KeyFlag::K_ENTER] = true;
                    break;
                case SDLK_LSHIFT:
                    key_state[KeyFlag::K_LSHIFT] = true;
                    break;
                default:
                    break;
                }
            }
            else if (ev.type == SDL_KEYUP) {
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key_state[KeyFlag::K_ESCAPE] = false;
                    break;
                case SDLK_LEFT:
                    key_state[KeyFlag::K_LEFT] = false;
                    break;
                case SDLK_RIGHT:
                    key_state[KeyFlag::K_RIGHT] = false;
                    break;
                case SDLK_UP:
                    key_state[KeyFlag::K_UP] = false;
                    break;
                case SDLK_DOWN:
                    key_state[KeyFlag::K_DOWN] = false;
                    break;
                case SDLK_SPACE:
                    key_state[KeyFlag::K_SPACE] = false;
                    break;
                case SDLK_LSHIFT:
                    key_state[KeyFlag::K_LSHIFT] = false;
                    break;
                default:
                    break;
                }
            }
        }
    }

    Vec2d randomPos(std::mt19937& rng, int w, int h)
    {
        std::uniform_real_distribution<double> xDist(0.0,
                                                     static_cast<double>(w));
        std::uniform_real_distribution<double> yDist(0.0,
                                                     static_cast<double>(h));

        return {xDist(rng), yDist(rng)};
    }


    std::mt19937 makeSeededRNG()
    {
        std::random_device randDev;
        auto rng = std::mt19937{ randDev() };
        std::mt19937::result_type seed_val{
            static_cast<unsigned long>(std::time(nullptr))
        };
        rng.seed(seed_val);

        return rng;
    }
}
