#pragma once

class Ship;

class Engine {
public:
    Engine(Ship *newOwner, double newPower, double newTurnSpeed);

    void on();
    void off();
    void turnLeft(double dt);
    void turnRight(double dt);

private:
    Ship *owner;
    double power;
    double turnSpeed;
};
