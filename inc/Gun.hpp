#pragma once

class PhysicsManager;
class Ship;

class Gun {
public:
    Gun(Ship& new_owner, double shotPower, double cooldown)
        : m_fired{ false }, m_owner{ new_owner }, m_shotPower{ shotPower },
          m_cooldown{ cooldown }, m_cooldownTimer{ 0.0 }
        {}

    void fire(PhysicsManager& physMan);
    void check_cooldown(double dt);
    void reset();

    bool fired() const { return m_fired; }

private:
    bool m_fired;
    Ship& m_owner;
    double m_shotPower;
    double m_cooldown;
    double m_cooldownTimer;
};
