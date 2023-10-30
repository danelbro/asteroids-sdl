#pragma once

#include <array>

#include <SDL.h>

#include "GameWorld.hpp"
#include "FlagEnums.hpp"

namespace GameLoop {
    void process_input(GameWorld& gw, Uint32 windowID,
                     std::array<bool,
                     KeyFlag::K_TOTAL> &key_state);
}
