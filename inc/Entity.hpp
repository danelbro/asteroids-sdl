#pragma once

// Entity class representing an on-screen object
// to be drawn with vector graphics

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class Entity {
public:
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual ~Entity() = default;

    Entity(const Entity&) = delete;
    Entity & operator=(const Entity&) = delete;

    Vec2d & pos() { return m_pos; }

    GameWorld const *gameWorld;

protected:
    Entity(GameWorld *new_gameWorld, Vec2d pos,
           std::vector<Vec2d> shape, SdlColor color, double scale)
    : gameWorld{ new_gameWorld }, m_pos{ pos },
      m_shape{ shape }, m_color{ color }, m_scale{ scale }
        {}

    Vec2d m_pos;
    std::vector<Vec2d> m_shape;
    SdlColor m_color;
    double m_scale;
};
