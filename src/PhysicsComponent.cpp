#include "../inc/PhysicsComponent.hpp"

#include <cmath>

#include <SDL.h>
#include <math.h>

#include "../inc/Box.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Entity.hpp"
#include "../inc/Vec2d.hpp"

void PhysicsComponent::turn(double turnSpeed)
{
    m_angle += turnSpeed;

    if (m_angle < 0)
        m_angle = 360 + m_angle;
    else if (m_angle >= 360)
        m_angle -= 360;
}

void PhysicsComponent::update()
{
    Vec2d dirVector{ std::cos((m_angle * M_PI) / 180),
                     std::sin((m_angle * M_PI) / 180) };
    auto totalForces{ dirVector * m_impulse };
    m_acceleration = totalForces / m_mass;
    m_velocity += m_acceleration;
    owner->pos() += m_velocity;
    m_impulse = 0;
}
