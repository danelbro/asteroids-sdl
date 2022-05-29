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

void wrap(Vec2d &pos, Box screen)
{
    if (pos.x < 0)
        pos.x = screen.w + pos.x;
    else if (pos.x > screen.w)
        pos.x -= screen.w;

    if (pos.y < 0)
        pos.y = screen.h + pos.y;
    else if (pos.y > screen.h)
        pos.y -= screen.h;
}

void PhysicsComponent::update(double elapsed)
{
    Vec2d dirVector{ std::sin((m_angle * M_PI) / 180),
                     -std::cos((m_angle * M_PI) / 180) };
    auto totalForces{ dirVector * m_impulse };
    m_acceleration = totalForces / m_mass * elapsed;
    m_velocity += m_acceleration * elapsed;
    owner->pos() += m_velocity * elapsed;
    wrap(owner->pos(), owner->gameWorld->screen);
    m_impulse = 0;
}

void PhysicsComponent::setAngle(double angle)
{
    if (angle < 0)
        m_angle = 360 + angle;
    else if (angle >= 360)
        m_angle = angle - 360;
    else
        m_angle = angle;

}
