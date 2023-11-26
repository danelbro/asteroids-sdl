﻿#pragma once

#include <random>
#include <vector>

#include "SDL_Interface.hpp"

#include "Hyperdrive.hpp"
#include "Ship.hpp"

struct GameWorld;
struct Vec2d;

class Player : public Ship {
public:
    Player(GameWorld& new_gameWorld, const Vec2d& pos,
           const std::vector<Vec2d>& shape, const utl::Colour& color,
           const double& scale, const double& power, const double& turnSpeed,
           const double& shotPower, const double& mass, std::mt19937& rng,
           const double& warpTimer, int lives, const double& respawnLength,
           const double& flashLength, const double& cooldown);

    void update(double, double) override;
    void respawn();

    void kill_it() override;

    bool isControllable() const { return m_isControllable; }
    bool isVulnerable() const { return m_isVulnerable; }
    int& lives() { return m_lives; }

    void setControllable(bool ctrl) { m_isControllable = ctrl; }
    void setVulnerable(bool vuln) { m_isVulnerable = vuln; }

    Hyperdrive hyperdrive;

private:
    void check_respawn(double dt);
    void check_flash(double dt);

    bool m_isControllable;
    bool m_isVulnerable;
    int m_lives;
    double m_respawnLength;
    double m_respawnTimer;
    bool m_isRespawning;
    double m_flashTimer;
    double m_flashLength;
};
