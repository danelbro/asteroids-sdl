#include "flags.hpp"

#include <string>

namespace utl {
    std::unordered_map<EntityFlag, std::string> entityMap{
            {EntityFlag::PLAYER, "PLAYER"},
            {EntityFlag::ASTEROID, "ASTEROID"},
            {EntityFlag::ENEMY, "ENEMY"},
            {EntityFlag::BULLET, "ENEMY_BULLET"},
            {EntityFlag::TEXT, "TEXT"}
    };

    std::unordered_map<std::string, EntityFlag> entityStringMap{
        {"PLAYER", EntityFlag::PLAYER},
        {"ASTEROID", EntityFlag::ASTEROID},
        {"ENEMY", EntityFlag::ENEMY},
        {"ENEMY_BULLET", EntityFlag::BULLET},
        {"TEXT", EntityFlag::TEXT}
    };

    std::unordered_map<StageID, std::string> stageMap{
        {StageID::TITLE_SCREEN, "TITLE_SCREEN"},
        {StageID::PLAYING, "PLAYING"},
        {StageID::GAME_OVER, "GAME_OVER"},
        {StageID::QUIT, "QUIT"}
    };

    std::unordered_map<std::string, StageID> stageStringMap{
        {"TITLE_SCREEN", StageID::TITLE_SCREEN},
        {"PLAYING", StageID::PLAYING},
        {"GAME_OVER", StageID::GAME_OVER},
        {"QUIT", StageID::QUIT}
    };
} // namespace utl