#pragma once

class PhysicsManager;
class Ship;

class Gun {
public:
    Gun(Ship& new_owner, double shotPower)
        : owner{ new_owner }, m_shotPower{ shotPower }
        {}

    void fire(PhysicsManager& physMan);
    bool fired{ false };

private:
    Ship& owner;
    double m_shotPower;
};
