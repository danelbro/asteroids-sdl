#pragma once

// Entity class representing an on-screen object

#include <array>
#include <memory>
#include <string>

#include <SDL.h>

#include "Box.hpp"
#include "KeyFlag.hpp"
#include "utility.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class Entity {
public:
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    SDL_Texture * texture() const { return m_texture.get(); }
    SDL_Rect & rect() { return m_rect; }
    SDL_Rect & oldRect() { return m_oldRect; }

    void setRect(int x, int y) { m_rect.x = x; m_rect.y = y;}
    void setRect(SDL_Rect newRect) { m_rect = newRect; }

    GameWorld const *gameWorld;

protected:
    Entity(std::string path, SDL_Renderer *renderer, GameWorld *new_gameWorld);
    void collide(SDL_Rect &dest, Box screen);

    const std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> m_texture{ nullptr };
    SDL_Rect m_rect{ };
    SDL_Rect m_oldRect{ };
};
