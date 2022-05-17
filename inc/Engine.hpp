#pragma once

#include "Ship.hpp"

class Player;

class Engine {
public:
    Engine(Ship &newOwner, double newPower, double newTurnSpeed);
    void on();
    void off();
    void turnLeft();
    void turnRight();

private:
    Ship &owner;
    double power;
    double turnSpeed;
};
