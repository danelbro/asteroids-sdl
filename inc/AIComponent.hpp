#pragma once

#include "Enemy.hpp"
#include "Player.hpp"

class AIComponent {
public:
    AIComponent();

    void update(double t, double dt, Player* plr);
    void setOwner(Enemy* new_owner);

private:
    Enemy* owner;
};
