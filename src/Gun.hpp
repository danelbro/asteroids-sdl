#pragma once

#include "Bullet.hpp"

class Gun {
public:
    Bullet fire();

private:
    Entity &owner;
};
