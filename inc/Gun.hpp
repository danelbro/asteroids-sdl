#pragma once

class PhysicsManager;
class GameWorld;
class Ship;

class Gun {
public:
    Gun(Ship *new_owner, double shotPower)
        : owner{ new_owner }, m_shotPower{ shotPower }
        {}

    void fire(GameWorld* new_GameWorld, PhysicsManager* physMan, Ship* firingShip);
    bool fired{ false };

private:
    Ship *owner;
    double m_shotPower;
};
