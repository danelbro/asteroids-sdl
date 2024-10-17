#include "Gun.hpp"

#include "Colors.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "flags.hpp"

#include <utl_VecGraphPhysComp.hpp>
#include <utl_SDLInterface.hpp>

void Gun::fire(PhysicsManager& physMan)
{
    utl::Colour col{};
    ENTITY_FLAG flag{};

    switch (ENTITY_STRING_MAP[m_owner.type()]) {
    case ENTITY_FLAG::PLAYER:
        col = customCols::bullet_col;
        flag = ENTITY_FLAG::BULLET;
        break;
    case ENTITY_FLAG::ENEMY:
        col = customCols::enemy_col;
        flag = ENTITY_FLAG::ENEMY_BULLET;
        break;
    default:
        break;
    }

    if (!m_fired) {
        physMan.make_bullet(m_owner.nose(), m_shotPower,
                            m_owner.physicsComponent.facing(), col, flag);
    }

    m_fired = true;
}

void Gun::check_cooldown(double dt)
{
    if (!m_fired) {
        return;
    }

    m_cooldownTimer += dt;
    if (m_cooldownTimer < m_cooldown) {
        return;
    }

    reset();
}

void Gun::reset()
{
    m_fired = false;
    m_cooldownTimer = 0.0;
}
