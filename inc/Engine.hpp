#pragma once

#include "Player.hpp"

class Player;

class Engine {
public:
    Engine(Player &newOwner, double newPower, double newTurnSpeed);
    void on();
    void off();
    void turnLeft();
    void turnRight();

private:
    Player &owner;
    double power;
    double turnSpeed;
};
