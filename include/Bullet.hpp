#pragma once

#include "flags.hpp"

#include <utl_GameWorld.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Vec2d.hpp>
#include <vector>

class Bullet : public utl::VecGraphPhysEnt {
public:
    Bullet(utl::GameWorld& new_gameWorld, const utl::Vec2d& pos,
           const std::vector<utl::Vec2d>& shape, const utl::Colour& color,
           const double& scale, const double& mass, const double& lifespan,
           const double& angle, const double& power, const ENTITY_FLAG& flag,
           bool wrap, bool fill);

    void update(double t, double dt) override;
    bool& wayward() { return m_wayward; }
    const double& lifespan() const { return m_lifespan; }

private:
    double m_lifespan;
    double m_alive{0.0};
    bool m_wayward;
};
