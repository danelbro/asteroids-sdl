#include "flags.hpp"

#include <string>

const std::unordered_map<ENTITY_FLAG, std::string> ENTITY_MAP{
    {ENTITY_FLAG::PLAYER, "PLAYER"},
    {ENTITY_FLAG::ASTEROID, "ASTEROID"},
    {ENTITY_FLAG::ENEMY, "ENEMY"},
    {ENTITY_FLAG::BULLET, "BULLET"},
    {ENTITY_FLAG::ENEMY_BULLET, "ENEMY_BULLET"},
    {ENTITY_FLAG::TEXT, "TEXT"},
    {ENTITY_FLAG::SCOREBOARD, "SCOREBOARD"}};

const std::unordered_map<std::string, ENTITY_FLAG> ENTITY_STRING_MAP{
    {"PLAYER", ENTITY_FLAG::PLAYER},
    {"ASTEROID", ENTITY_FLAG::ASTEROID},
    {"ENEMY", ENTITY_FLAG::ENEMY},
    {"BULLET", ENTITY_FLAG::BULLET},
    {"ENEMY_BULLET", ENTITY_FLAG::ENEMY_BULLET},
    {"TEXT", ENTITY_FLAG::TEXT},
    {"SCOREBOARD", ENTITY_FLAG::SCOREBOARD}};

const std::unordered_map<STAGE_ID, std::string> STAGE_MAP{
    {STAGE_ID::TITLE_SCREEN, "TITLE_SCREEN"},
    {STAGE_ID::PLAYING, "PLAYING"},
    {STAGE_ID::GAME_OVER, "GAME_OVER"},
    {STAGE_ID::HIGH_SCORES, "HIGH_SCORES"},
    {STAGE_ID::QUIT, "QUIT"}};

const std::unordered_map<std::string, STAGE_ID> STAGE_STRING_MAP{
    {"TITLE_SCREEN", STAGE_ID::TITLE_SCREEN},
    {"PLAYING", STAGE_ID::PLAYING},
    {"GAME_OVER", STAGE_ID::GAME_OVER},
    {"HIGH_SCORES", STAGE_ID::HIGH_SCORES},
    {"QUIT", STAGE_ID::QUIT}};
