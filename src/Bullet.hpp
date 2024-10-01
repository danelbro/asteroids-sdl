#pragma once

#include <vector>

#include "flags.hpp"
#include "PhysicsEntity.hpp"
#include "SDL_Interface.hpp"

struct GameWorld;
struct Vec2d;

class Bullet : public PhysicsEntity {
public:
    Bullet(GameWorld& new_gameWorld, const Vec2d& pos,
           const std::vector<Vec2d>& shape, const utl::Colour& color,
           const double& scale, const double& mass, const double& lifespan,
           const double& angle, const double& power,
           const utl::EntityFlag& flag);

    void update(double t, double dt) override;
    bool& wayward() { return m_wayward; }
    const double& lifespan() const { return m_lifespan; }

private:
    double m_lifespan;
    double m_alive{ 0.0 };
    bool m_wayward;
};
