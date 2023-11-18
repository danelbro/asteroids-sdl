#pragma once

#include <array>
#include <unordered_map>
#include <memory>

#include <SDL.h>

#include "Stage.hpp"
#include "utility.hpp"

class StageManager {
public:
    StageManager(utl::StageID first);

    void add_stage(utl::StageID key, std::unique_ptr<Stage> new_stage);
    void run();
private:
    void handle_stage_transition(Stage* current_stage);

    std::unordered_map<utl::StageID, std::unique_ptr<Stage>> stages{ };
    utl::StageID current;
    utl::StageID next;
    std::array<bool, static_cast<size_t>(utl::KeyFlag::K_TOTAL)> keyState{ };
};
