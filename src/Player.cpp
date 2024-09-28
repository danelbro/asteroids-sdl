#include "Player.hpp"

#include <random>
#include <vector>

#include "SDL_Interface.hpp"

#include "Colors.hpp"
#include "flags.hpp"
#include "GameWorld.hpp"
#include "Hyperdrive.hpp"
#include "PhysicsComponent.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

Player::Player(GameWorld& new_gameWorld, const Vec2d& pos,
               const std::vector<Vec2d>& shape, const utl::Colour& color,
               const double& scale, const double& power,
               const double& turnSpeed, const double& shotPower,
               const double& mass, std::mt19937& rng,
               const double& warpLength, int lives,
               const double& respawnLength, const double& flashLength,
               const double& cooldown)
    : Ship{utl::EntityFlag::PLAYER, new_gameWorld, pos, shape, color, scale,
           power, turnSpeed, shotPower, mass, cooldown},
      hyperdrive{ *this, warpLength, rng }, m_isControllable{ true },
      m_isVulnerable{ true }, m_lives{ lives },
      m_respawnLength{ respawnLength }, m_respawnTimer{ 0.0 },
      m_isRespawning{ false }, m_flashTimer{ 0.0 },
      m_flashLength{ flashLength }
{
    // fill = true;
}

void Player::update(double, double dt)
{
    gun.check_cooldown(dt);
    hyperdrive.check_warp(dt);
    check_flash(dt);
    check_respawn(dt);
    update_shapes();
}

void Player::kill_it()
{
    if (!m_isVulnerable) return;

    if (--m_lives > 0) respawn();
}

void Player::respawn()
{
    if (m_isRespawning) return;

    m_respawnTimer = 0.0;
    m_flashTimer = 0.0;
    m_isRespawning = true;
    m_isVulnerable = false;
    m_isVisible = false;
    physicsComponent.setAcceleration({0, 0});
    physicsComponent.setFrameImpulse(0);
    physicsComponent.setVelocity({0, 0});
    m_pos = { gameWorld.screen.w / 2.0, gameWorld.screen.h / 2.0 };
}

void Player::check_respawn(double dt)
{
    if (!m_isRespawning) return;
    m_respawnTimer += dt;

    if (m_respawnTimer >= m_respawnLength) {
        m_isRespawning = false;
        m_isVisible = true;
        m_isVulnerable = true;
    }
}

void Player::check_flash(double dt)
{
    if (!m_isRespawning) return;

    m_flashTimer += dt;
    if (m_flashTimer >= m_flashLength) {
        m_flashTimer = 0.0;
        m_isVisible = m_isVisible ? false : true;
    }
}
