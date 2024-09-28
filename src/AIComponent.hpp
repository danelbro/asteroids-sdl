#pragma once

#include "PhysicsManager.hpp"
#include "Player.hpp"

class Enemy;

class AIComponent {
public:
    AIComponent(Enemy& new_owner, PhysicsManager& physMan);

    void update(double t, double dt, Player* plr);
private:
    void random_update(double t, double dt);

    Enemy& m_owner;
    PhysicsManager& m_physMan;
};
