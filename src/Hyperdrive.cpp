#include "../inc/Hyperdrive.hpp"

#include <iostream>

#include "../inc/Player.hpp"

Hyperdrive::Hyperdrive(Player* new_owner, double warpTimer)
    : isWarping{ false }, m_warpTimer{ warpTimer }, owner{ new_owner }
{}

void Hyperdrive::warp() {
    if (!isWarping) {
        std::cout << "Warping!";
        isWarping = true;
    }
}
