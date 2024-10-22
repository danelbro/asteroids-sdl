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
    SCOREBOARD,
    E_TYPE_TOTAL
};

const extern std::unordered_map<ENTITY_FLAG, std::string> ENTITY_MAP;

const extern std::unordered_map<std::string, ENTITY_FLAG> ENTITY_STRING_MAP;

enum class STAGE_ID
{
    TITLE_SCREEN,
    PLAYING,
    GAME_OVER,
    HIGH_SCORES,
    STAGES_TOTAL,
    QUIT
};

const extern std::unordered_map<STAGE_ID, std::string> STAGE_MAP;

const extern std::unordered_map<std::string, STAGE_ID> STAGE_STRING_MAP;
