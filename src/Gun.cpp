#include "Gun.hpp"

#include "Colors.hpp"
#include "flags.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsManager.hpp"
#include "SDL_Interface.hpp"
#include "Ship.hpp"
#include "utility.hpp"

void Gun::fire(PhysicsManager& physMan)
{
    utl::Colour col{};
    utl::EntityFlag flag{};
    switch (utl::entityStringMap[m_owner.type()]) {
    case utl::EntityFlag::PLAYER:
        col = utl::customCols::bullet_col;
        flag = utl::EntityFlag::BULLET;
        break;
    case utl::EntityFlag::ENEMY:
        col = utl::customCols::enemy_col;
        flag = utl::EntityFlag::ENEMY_BULLET;
        break;
    default:
        break;
    }

    if (!m_fired)
        physMan.make_bullet(m_owner.nose(), m_shotPower,
                            m_owner.physicsComponent.angle(),
                            col, flag);

    m_fired = true;
}

void Gun::check_cooldown(double dt)
{
    if (!m_fired) return;

    m_cooldownTimer += dt;
    if (m_cooldownTimer < m_cooldown) return;

    reset();
}

void Gun::reset()
{
    m_fired = false;
    m_cooldownTimer = 0.0;
}
