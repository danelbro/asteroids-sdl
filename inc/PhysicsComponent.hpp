#pragma once

#include <SDL.h>

#include "Box.hpp"
#include "Vec2d.hpp"

class Entity;

class PhysicsComponent {
public:
    PhysicsComponent(double mass, Entity *new_owner)
        : m_mass { mass }, m_impulse{ 0.0 }, m_acceleration{ 0.0, 0.0 },
          m_velocity{ 0, 0 }, m_angle{ 0.0 },
          owner { new_owner }
        {}

    void setFrameImpulse(double power) { m_impulse = power; }
    void turn(double turnSpeed);

    double angle() const { return m_angle; }
    Vec2d velocity() const { return m_velocity; }

    void setAngle(double angle);
    void setOwner(Entity *new_owner) { owner = new_owner; }

    void update();

private:
    const double m_mass;
    double m_impulse;
    Vec2d m_acceleration;
    Vec2d m_velocity;

    double m_angle; // between 0 and 360

    Entity *owner;
};
