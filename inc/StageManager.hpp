#pragma once

#include <algorithm>
#include <array>
#include <unordered_map>
#include <memory>

#include <SDL.h>

#include "FlagEnums.hpp"

class Stage;

class StageManager {
public:
    StageManager();

    void add_stage(StageID key, std::unique_ptr<Stage> new_stage);
    void run();
private:
    bool handle_stage_transition();

    std::unordered_map<StageID, std::unique_ptr<Stage>> stages{ };
    StageID current{StageID::PLAYING};
    StageID next{StageID::PLAYING};
    std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)> keyState{ };
};
