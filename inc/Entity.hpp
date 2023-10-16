#pragma once

// Entity class representing an on-screen object
// to be drawn with vector graphics

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "FlagEnums.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class Entity {
public:
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void update(double t, double dt) = 0;

    virtual ~Entity() = default;
    Entity(const Entity&) = delete;
    Entity & operator=(const Entity&) = delete;

    Vec2d & pos() { return m_pos; }
    bool toBeKilled() const { return kill_me; }
    void kill_it() { kill_me = true; }
    double scale() const { return m_scale; }

    EntityFlag type;
    GameWorld *gameWorld;

protected:
    Entity(EntityFlag new_type, GameWorld* new_gameWorld, Vec2d pos,
        std::vector<Vec2d> shape, SdlColor color, double scale)
        : type{ new_type }, gameWorld{ new_gameWorld }, m_pos{ pos },
        m_shape{ shape }, m_color{ color }, m_scale{ scale }
    {}

    Vec2d m_pos;
    std::vector<Vec2d> m_shape;
    SdlColor m_color;
    double m_scale;
    bool kill_me{ false };
    bool fill{ false };
};
