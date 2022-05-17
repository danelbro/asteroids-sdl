#pragma once

#include "Entity.hpp"
#include "Vec2d.hpp"

class PhysicsComponent {
public:
    PhysicsComponent();

    void setFrameAcceleration(double power) { accelerationMag = power; }
    void setFrameTurn(double turnSpeed) { turnAmount = turnSpeed; }

    Vec2d facing_direction() const { return m_facing_direction; }
    Vec2d velocity() const { return m_velocity; }

private:
    const double mass;
    double accelerationMag;
    Vec2d acceleration;
    Vec2d m_velocity;

    double turnAmount;
    Vec2d m_facing_direction;
    Vec2d velocity_direction;

    Entity &owner;
};
