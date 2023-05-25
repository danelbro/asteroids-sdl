#pragma once

#include "EntityManager.hpp"

class Ship;

class Gun {
public:
    Gun(Ship *new_owner, double shotPower)
        : owner{ new_owner }, m_shotPower{ shotPower }
        {}

    void fire(EntityManager *entMan);

private:
    Ship *owner;
    double m_shotPower;
};
