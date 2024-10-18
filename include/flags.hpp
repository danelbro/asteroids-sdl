#pragma once

#include <string>
#include <unordered_map>

enum class ENTITY_FLAG
{
    PLAYER,
    ASTEROID,
    ENEMY,
    BULLET,
    ENEMY_BULLET,
    TEXT,
    E_TYPE_TOTAL
};

extern std::unordered_map<ENTITY_FLAG, std::string> ENTITY_MAP;

extern std::unordered_map<std::string, ENTITY_FLAG> ENTITY_STRING_MAP;

enum class STAGE_ID
{
    TITLE_SCREEN,
    PLAYING,
    GAME_OVER,
    HIGH_SCORES,
    STAGES_TOTAL,
    QUIT
};

extern std::unordered_map<STAGE_ID, std::string> STAGE_MAP;

extern std::unordered_map<std::string, STAGE_ID> STAGE_STRING_MAP;
