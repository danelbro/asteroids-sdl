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
    StageManager(StageID first);

    void add_stage(StageID key, std::unique_ptr<Stage> new_stage);
    void run();
private:
    void handle_stage_transition(Stage* current_stage);

    std::unordered_map<StageID, std::unique_ptr<Stage>> stages{ };
    StageID current;
    StageID next;
    std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)> keyState{ };
};
