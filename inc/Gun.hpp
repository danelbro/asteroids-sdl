#pragma once

#include "Bullet.hpp"
#include "Ship.hpp"

class Gun {
public:
    Gun();

    Bullet fire();

private:
    Ship &owner;
};
