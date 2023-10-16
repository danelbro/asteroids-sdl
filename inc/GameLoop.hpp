#pragma once

#include <array>

#include <SDL.h>

#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "FlagEnums.hpp"
#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"

namespace GameLoop {
    void process_input(GameWorld* gw, Uint32 windowID,
                     std::array<bool,
                     static_cast<size_t>(KeyFlag::K_TOTAL)> &key_state);
}
