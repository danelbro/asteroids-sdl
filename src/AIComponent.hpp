#pragma once

#include <random>

#include "PhysicsManager.hpp"
#include "Player.hpp"

class Enemy;

class AIComponent {
public:
    AIComponent(Enemy& owner, PhysicsManager& physMan, std::mt19937& rng);

    void update(double t, double dt, Player* plr);
private:
    Enemy& m_owner;
    PhysicsManager& m_physMan;
    std::mt19937& m_rng;
    double turnTime;
    double sinceTurn;
};
