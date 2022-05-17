#pragma once

// Entity class representing an on-screen object

#include <array>
#include <memory>
#include <string>

#include <SDL.h>

#include "KeyFlag.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

class Entity {
public:
    virtual void update() = 0;
    virtual void render(SDL_Renderer *renderer, double progress) = 0;
    virtual ~Entity() = default;

    SDL_Texture * texture() const { return m_texture.get(); }
    SDL_Rect rect() const { return m_rect; }

    void setRect(SDL_Rect newRect) { m_rect = newRect; }

    GameWorld const &gameWorld;


protected:
    Entity(std::string path, SDL_Renderer *renderer, GameWorld &new_gameWorld);
    const std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> m_texture{ nullptr };
    void collide(SDL_Rect &dest, Box screen);


    SDL_Rect m_rect{ };
    SDL_Rect old_rect{ };
};
