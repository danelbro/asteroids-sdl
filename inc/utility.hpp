#pragma once

#include <fstream>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

struct GameWorld;
struct Vec2d;

namespace utl {
    extern std::ofstream errorLogger;

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
        WINDOW_CHANGE,
        K_TOTAL
    };

    // process SDL input into a more friendly form. Also deals withh
    // window resizing
    void process_input(GameWorld& gw, Uint32 windowID,
                     std::array<bool,
                     KeyFlag::K_TOTAL> &key_state);

    Vec2d randomPos(std::mt19937& rng, int w, int h);

    std::mt19937 makeSeededRNG();

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
}
