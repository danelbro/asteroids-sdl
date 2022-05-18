#pragma once

class Ship;

class Gun {
public:
    Gun(Ship *new_owner, double shotPower)
        : owner{ new_owner }, m_shotPower{ shotPower }
        {}

    void fire();

private:
    Ship *owner;
    double m_shotPower;
};
