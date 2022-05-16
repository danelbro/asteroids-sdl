#include "../inc/utility.hpp"

#include <memory>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "../inc/Entity.hpp"

const char* SdlException::what() const throw() {
    return SDL_GetError();
}

const char* ImgException::what() const throw() {
    return IMG_GetError();
}

void init(u_int32_t sdlFlags, u_int32_t imgFlags)
{
    if (SDL_Init(sdlFlags) != 0)
        throw SdlException();

    if (!(static_cast<u_int32_t>(IMG_Init(static_cast<int>(imgFlags)))
          & imgFlags)) {
        throw ImgException();
    }
}

SDL_Window* createWindow(const char* title, int x, int y,
                          int w, int h, Uint32 flags)
{
    SDL_Window *window = nullptr;

    window = SDL_CreateWindow(title, x, y, w, h ,flags);

    if (!window)
        throw SdlException();

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window, int index, Uint32 flags)
{
    SDL_Renderer *rend = nullptr;
    rend = SDL_CreateRenderer(window, index, flags);

    if (!rend)
        throw SdlException();

    return rend;
}

SDL_Texture* loadMedia(std::string path, SDL_Renderer* rend)
{
    SDL_Texture *tex = nullptr;
    SDL_Surface *img = nullptr;
    img = IMG_Load(path.c_str());

    if (!img)
        throw ImgException();

    SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0, 255, 255));

    tex = SDL_CreateTextureFromSurface(rend, img);

    if (!tex)
        throw ImgException();

    SDL_FreeSurface(img);
    img = nullptr;

    return tex;
}

