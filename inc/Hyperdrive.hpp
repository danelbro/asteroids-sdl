#pragma once

class Player;

class Hyperdrive {
public:
    Hyperdrive(Player& new_owner, double warpTimer);

    void warp();

private:
    bool isWarping;
    double m_warpTimer;
    Player& owner;
};
