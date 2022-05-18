#include "../inc/Entity.hpp"

#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/KeyFlag.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

extern const SdlColor bg;
extern const SdlColor debug;

Entity::Entity(std::string path, SDL_Renderer *renderer,
               GameWorld *new_gameWorld)
    : gameWorld{ new_gameWorld },
      m_texture{ std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> {
            loadMedia(path, renderer)} },
      m_rect{ }, m_oldRect{ m_rect }
{
    SDL_QueryTexture(m_texture.get(), NULL, NULL, &m_rect.w, &m_rect.h);
}

