#pragma once

#include <array>
#include <random>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Box.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "Stage.hpp"
#include "utility.hpp"

class MainLevel : public Stage {
public:
    MainLevel(Box screen, Uint32 windowID, SDL_Renderer* renderer);

    StageID handle_input(double t, double dt,
                         std::array<bool,
                         static_cast<size_t>(
                             KeyFlag::K_TOTAL)>& key_state) override;
    StageID update(double t, double dt) override;
    void render(double t, double dt) override;
private:
    GameWorld gameWorld;
    PhysicsManager physicsManager;
    ScoreManager scoreManager;
    std::mt19937 rng;
    std::unique_ptr<TTF_Font, sdl_deleter> font;
    Player* player;
    bool asteroidsRemain;
    int numOfAsteroids;
};
