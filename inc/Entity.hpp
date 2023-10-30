#pragma once

// Entity class representing an on-screen object
// to be drawn with vector graphics

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

class Entity {
public:
    virtual ~Entity() = default;

    virtual void update(double t, double dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

    virtual Vec2d& pos() { return m_pos; }
    virtual bool toBeKilled() const { return kill_me; }
    virtual void kill_it() { kill_me = true; }
    virtual double scale() const { return m_scale; }

    utl::EntityFlag type;
    GameWorld& gameWorld;

protected:
    Entity(utl::EntityFlag new_type, GameWorld& new_gameWorld, Vec2d pos,
        std::vector<Vec2d> shape, SdlColor color, double scale)
        : type{ new_type }, gameWorld{ new_gameWorld }, m_pos{ pos },
        m_shape{ shape }, m_color{ color }, m_scale{ scale },
        kill_me{ false }, fill{ false }
    {}

    Vec2d m_pos;
    std::vector<Vec2d> m_shape;
    SdlColor m_color;
    double m_scale;
    bool kill_me;
    bool fill;
};
