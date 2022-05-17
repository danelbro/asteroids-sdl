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

    SDL_Texture * getTex() const { return texture.get(); }
    SDL_Rect getRect() const { return rect; }

protected:
    Entity(std::string path, SDL_Renderer *renderer, GameWorld &new_gameWorld);
    std::unique_ptr<SDL_Texture, SDL_TextureDestroyer> texture{ nullptr };
    SDL_Rect rect{ };
    SDL_Rect old_rect{ };
    GameWorld &gameWorld;
};

