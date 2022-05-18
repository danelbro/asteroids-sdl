#include "../inc/PhysicsComponent.hpp"

#include <SDL.h>

#include "../inc/Box.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Entity.hpp"
#include "../inc/Vec2d.hpp"

void PhysicsComponent::update()
{
    owner->oldRect() = owner->rect();

    m_facingDirection = m_facingDirection.rotate_deg(m_turnAmount);
    m_facingDirection.normalizeInPlace();

    double drag { 0.5 * owner->gameWorld->fluidDensity *
        m_velocity.magnitude_squared() };

    if (m_velocity.magnitude() == 0)
        m_velocityDirection.update(0, 0);
    else
        m_velocityDirection = m_velocity.normalize();

    auto totalForces{ ((m_facingDirection * m_accelerationMag)
                       + (-m_velocityDirection * drag)) };

    m_acceleration = totalForces / m_mass;

    m_velocity = m_velocity + m_acceleration;

    owner->rect().x -= m_velocity.x;
    owner->rect().y -= m_velocity.y;

    checkBounds(owner->rect(), owner->gameWorld->screen);

    m_accelerationMag = 0;
    m_turnAmount = 0;
}

void PhysicsComponent::checkBounds(SDL_Rect &dest, Box screen)
{
    if (dest.x < -owner->rect().w)
        dest.x = screen.w;
    else if (dest.x > screen.w)
        dest.x = -owner->rect().w;

    if (dest.y < -owner->rect().h)
        dest.y = screen.h;
    else if (dest.y > screen.h)
        dest.y = -owner->rect().h;

}
