#include "../inc/Entity.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/DirFlag.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

extern const SdlColor bg;
extern const SdlColor debug;

Entity::Entity(std::string path, SDL_Renderer *renderer,
               GameWorld &new_gameWorld)
    : texture{ nullptr }, rect{ }, old_rect{ rect }, gameWorld{ new_gameWorld }
{
    texture = std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> {loadMedia(path, renderer)};
    SDL_QueryTexture(texture.get(), NULL, NULL, &rect.w, &rect.h);
}

