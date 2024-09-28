#pragma once

#include <string>
#include <unordered_map>

namespace utl {
    enum class EntityFlag {
        PLAYER,
        ASTEROID,
        ENEMY,
        BULLET,
        ENEMY_BULLET,
        TEXT,
        E_TYPE_TOTAL
    };

    extern std::unordered_map<EntityFlag, std::string> entityMap;

    extern std::unordered_map<std::string, EntityFlag> entityStringMap;

    enum class StageID {
        TITLE_SCREEN,
        PLAYING,
        GAME_OVER,
        STAGES_TOTAL,
        QUIT
    };

    extern std::unordered_map<StageID, std::string> stageMap;

    extern std::unordered_map<std::string, StageID> stageStringMap;
}