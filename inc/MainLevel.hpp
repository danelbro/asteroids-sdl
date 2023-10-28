#pragma once

#include <array>
#include <memory>
#include <random>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Box.hpp"
#include "FlagEnums.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "Stage.hpp"
#include "utility.hpp"

class MainLevel : public Stage {
public:
    MainLevel(Box screen, Uint32 windowID, SDL_Renderer* renderer);

    MainLevel(const MainLevel&) = delete;
    MainLevel& operator=(const MainLevel&) = delete;
    ~MainLevel() = default;

    StageID handle_input(double t, double dt,
        std::array<bool, KeyFlag::K_TOTAL>& key_state) override;
    StageID update(double t, double dt) override;
    void render(double t, double dt) override;

    PhysicsManager& physMan() { return physicsManager; }
    ScoreManager& scoreMan() { return scoreManager; }
private:
    void init();

    GameWorld gameWorld;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> font;
    PhysicsManager physicsManager;
    std::mt19937 rng;
    Player* player;
    ScoreManager scoreManager;
    bool asteroidsRemain;
    int numOfAsteroids;
    bool enemiesRemain;
    double levelElapsedTime;
};
