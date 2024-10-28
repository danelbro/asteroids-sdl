#pragma once

#include "PhysicsManager.hpp"
#include "Player.hpp"

#include <utl_random.hpp>

class Enemy;

class AIComponent {
public:
    AIComponent(Enemy& owner, PhysicsManager& physMan, utl::RNG& rng);

    void update(double t, double dt, Player* plr, bool isScreenClear);

private:
    Enemy& m_owner;
    PhysicsManager& m_physMan;
    utl::RNG& m_rng;
    double m_turnTimeLower;
    double m_turnTimeUpper;
    std::uniform_real_distribution<double> m_turnTimeDist;
    double m_turnTime;
    double m_timeSinceTurn;
    double m_targetAngle;
    double m_enginePulse;
    double m_timeSincePulse;
};
