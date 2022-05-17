#pragma once

#include "Bullet.hpp"
#include "Entity.hpp"

class Gun {
public:
    Gun();

    Bullet fire();

private:
    Entity &owner;
};
