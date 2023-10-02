#pragma once

#include "AIComponent.hpp"
#include "Ship.hpp"

class Enemy : public Ship {
public:
    Enemy();

    ~Enemy() = default;
    Enemy(const Enemy&) = delete;
    Enemy& operator=(const Enemy&) = delete;

    AIComponent *aiComponent;
};
