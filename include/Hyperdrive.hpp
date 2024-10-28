#pragma once

#include "utl_random.hpp"

class Player;

class Hyperdrive {
public:
    Hyperdrive(Player& new_owner, double warpLength, utl::RNG& rng);

    void warp();
    void check_warp(double dt);
    void stop_warp();

    bool isWarping() const { return m_isWarping; }
    double warpTimer() const { return m_warpTimer; }

private:
    bool m_isWarping;
    double m_warpLength;
    double m_warpTimer;
    Player& m_owner;
    utl::RNG& m_rng;
};
