#include "flags.hpp"

#include <string>

std::unordered_map<ENTITY_FLAG, std::string> ENTITY_MAP{
    {ENTITY_FLAG::PLAYER, "PLAYER"},
    {ENTITY_FLAG::ASTEROID, "ASTEROID"},
    {ENTITY_FLAG::ENEMY, "ENEMY"},
    {ENTITY_FLAG::BULLET, "ENEMY_BULLET"},
    {ENTITY_FLAG::TEXT, "TEXT"}};

std::unordered_map<std::string, ENTITY_FLAG> ENTITY_STRING_MAP{
    {"PLAYER", ENTITY_FLAG::PLAYER},
    {"ASTEROID", ENTITY_FLAG::ASTEROID},
    {"ENEMY", ENTITY_FLAG::ENEMY},
    {"ENEMY_BULLET", ENTITY_FLAG::BULLET},
    {"TEXT", ENTITY_FLAG::TEXT}};

std::unordered_map<STAGE_ID, std::string> STAGE_MAP{
    {STAGE_ID::TITLE_SCREEN, "TITLE_SCREEN"},
    {STAGE_ID::PLAYING, "PLAYING"},
    {STAGE_ID::GAME_OVER, "GAME_OVER"},
    {STAGE_ID::QUIT, "QUIT"}};

std::unordered_map<std::string, STAGE_ID> STAGE_STRING_MAP{
    {"TITLE_SCREEN", STAGE_ID::TITLE_SCREEN},
    {"PLAYING", STAGE_ID::PLAYING},
    {"GAME_OVER", STAGE_ID::GAME_OVER},
    {"QUIT", STAGE_ID::QUIT}};
