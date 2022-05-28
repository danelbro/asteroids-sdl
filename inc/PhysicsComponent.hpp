#pragma once

#include <SDL.h>

#include "Box.hpp"
#include "Vec2d.hpp"

class Entity;

class PhysicsComponent {
public:
    PhysicsComponent(double mass, Entity *new_owner)
        : m_mass { mass }, m_accelerationMag{ 0.0 }, m_acceleration{ 0.0, 0.0 },
          m_velocity{ 0, 0 }, m_turnAmount{ 0.0 },
          m_facingDirection{ 0.0, -1.0 }, m_velocityDirection{ 0.0, 0.0 },
          owner { new_owner }
        {}

    void setFrameAcceleration(double power) { m_accelerationMag = power; }
    void setFrameTurn(double turnSpeed) { m_turnAmount = turnSpeed; }

    Vec2d facing_direction() const { return m_facingDirection; }
    Vec2d velocity() const { return m_velocity; }

    void setOwner(Entity *new_owner) { owner = new_owner; }

    void update();

private:
    const double m_mass;
    double m_accelerationMag;
    Vec2d m_acceleration;
    Vec2d m_velocity;

    double m_turnAmount;
    Vec2d m_facingDirection;
    Vec2d m_velocityDirection;

    Entity *owner;
};
