#pragma once

enum KeyFlag {
    K_LEFT,
    K_RIGHT,
    K_UP,
    K_DOWN,
    K_SPACE,
    K_ENTER,
    K_LSHIFT,
    K_ESCAPE,
    QUIT,
    K_TOTAL
};

enum class EntityFlag {
    PLAYER,
    ASTEROID,
    ENEMY,
    BULLET,
    ENEMY_BULLET,
    TEXT,
    E_TYPE_TOTAL
};

enum class StageID {
    TITLE_SCREEN,
    PLAYING,
    HIGH_SCORES,
    STAGES_TOTAL,
    QUIT
};
