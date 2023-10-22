#pragma once

#include <array>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Hyperdrive.hpp"
#include "PhysicsEntity.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class PhysicsComponent;

class Player : public Ship {
public:
    Player(GameWorld& new_gameWorld, Vec2d pos,
           std::vector<Vec2d> shape, SdlColor color, double scale,
           double power, double turnSpeed,
           double shotPower,
           PhysicsComponent *physComp, std::mt19937& rng,
           double warpTimer, int lives, double respawnLength,
           double flashLength);

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
