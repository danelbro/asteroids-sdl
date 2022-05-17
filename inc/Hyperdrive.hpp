#pragma once

#include "Entity.hpp"

class Hyperdrive {
public:
    Hyperdrive();

    void warp();

private:
    Entity &owner;
};
