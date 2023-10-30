#pragma once

#include <array>
#include <memory>
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

    MainLevel(const MainLevel&) = delete;
    MainLevel& operator=(const MainLevel&) = delete;
    ~MainLevel() = default;

    utl::StageID handle_input(double t, double dt,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    utl::StageID update(double t, double dt) override;
    void render(double t, double dt) override;

    PhysicsManager& physMan() { return physicsManager; }
    ScoreManager& scoreMan() { return scoreManager; }
private:
    void init();

    std::unique_ptr<TTF_Font, utl::sdl_deleter> font;
    GameWorld gameWorld;
    std::mt19937 rng;
    PhysicsManager physicsManager;
    Player& player;
    ScoreManager scoreManager;
    bool asteroidsRemain;
    int numOfAsteroids;
    bool enemiesRemain;
    double levelElapsedTime;
};
