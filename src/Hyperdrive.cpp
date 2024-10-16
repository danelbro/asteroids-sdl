#include "Hyperdrive.hpp"

#include "Player.hpp"

#include <random>
#include <utl_PhysicsComponent.hpp>

Hyperdrive::Hyperdrive(Player& owner, double warpLength, std::mt19937& rng)
    : m_isWarping{false}, m_warpLength{warpLength}, m_warpTimer{0.0},
      m_owner{owner}, m_rng{rng}
{}

void Hyperdrive::warp()
{
    if (m_isWarping) {
        return;
    }

    m_warpTimer = 0.0;
    m_isWarping = true;
    m_owner.setVulnerable(false);
    m_owner.setVisible(false);
    m_owner.setControllable(false);

    m_owner.physicsComponent.setAcceleration({0, 0});
    m_owner.physicsComponent.setFrameImpulse(0);
    m_owner.physicsComponent.setVelocity({0, 0});

    m_owner.set_pos(
        utl::randomPos(m_rng, m_owner.screen().w, m_owner.screen().h));
}

void Hyperdrive::check_warp(double dt)
{
    if (!m_isWarping) {
        return;
    }

    m_warpTimer += dt;

    if (m_warpTimer >= m_warpLength) {
        stop_warp();
    }
}

void Hyperdrive::stop_warp()
{
    if (!m_isWarping) {
        return;
    }

    m_isWarping = false;
    m_owner.setVulnerable(true);
    m_owner.setVisible(true);
    m_owner.setControllable(true);
}
