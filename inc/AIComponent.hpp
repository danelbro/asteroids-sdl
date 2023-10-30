#pragma once

#include "Player.hpp"

class Enemy;

class AIComponent {
public:
    AIComponent(Enemy& new_owner);

    void update(double t, double dt, Player* plr);
private:
    Enemy& owner;
};
