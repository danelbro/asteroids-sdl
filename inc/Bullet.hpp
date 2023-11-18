#pragma once

#include <vector>

#include <SDL.h>

#include "PhysicsEntity.hpp"
#include "utility.hpp"

struct GameWorld;
struct Vec2d;

class Ship;
class PhysicsComponent;

class Bullet : public PhysicsEntity {
public:
    Bullet(GameWorld& new_gameWorld, Vec2d pos, std::vector<Vec2d> shape,
           SdlColor color, double scale, double mass, double lifespan,
           double angle, double power, utl::EntityFlag flag);

    void update(double t, double dt) override;
    bool& wayward() { return m_wayward; }

private:
    double m_lifespan;
    double m_alive{ 0.0 };
    bool m_wayward;
};
