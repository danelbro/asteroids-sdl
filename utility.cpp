#include "utility.h"

#include <sstream>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

const char* Sdl_exception::what() const throw() {
    return SDL_GetError();
}

const char* Img_exception::what() const throw() {
    return IMG_GetError();
}

void init(Uint32 sdl_flags, Uint32 img_flags)
{
    if (SDL_Init(sdl_flags) != 0)
        throw Sdl_exception();

    if (!(IMG_Init(img_flags) & img_flags)) {
        throw Img_exception();
    }
}

SDL_Window* create_window(const char* title, int x, int y,
                          int w, int h, Uint32 flags)
{
    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(title, x, y, w, h ,flags);

    if (!window)
        throw Sdl_exception();

    return window;
}

SDL_Renderer* create_renderer(SDL_Window* window, int index, Uint32 flags)
{
    SDL_Renderer *rend = nullptr;
    rend = SDL_CreateRenderer(window, index, flags);

    if (!rend)
        throw Sdl_exception();

    return rend;
}

SDL_Texture* load_media(std::string path, SDL_Renderer* rend,
                        SDL_Texture* tex)
{
    tex = IMG_LoadTexture(rend, path.c_str());

    if (!tex)
        throw Img_exception();

    return tex;
}

void close(SDL_Renderer *renderer, SDL_Window *window,
           std::vector<SDL_Texture*> textures)
{
    for (auto &tex : textures)
        SDL_DestroyTexture(tex);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
