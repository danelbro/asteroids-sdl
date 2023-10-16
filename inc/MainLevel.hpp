#pragma once

#include <array>
#include <random>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Box.hpp"
#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Player.hpp"
#include "ScoreManager.hpp"
#include "Stage.hpp"
#include "utility.hpp"

class MainLevel : public Stage {
public:
    MainLevel(Box screen, Uint32 windowID, SDL_Renderer* renderer);

    ~MainLevel();

    MainLevel(const MainLevel&) = delete;
    MainLevel& operator=(const MainLevel&) = delete;

    StageID handle_input(double t, double dt,
                         std::array<bool,
                         static_cast<size_t>(KeyFlag::K_TOTAL)>& key_state);
    StageID update(double t, double dt);
    void render(double t, double dt);
private:
    GameWorld gameWorld;
    EntityManager entityManager;
    PhysicsManager physicsManager;
    ScoreManager scoreManager;
    std::mt19937 rng;
    TTF_Font* font;
    Player* player;
    bool asteroidsRemain;
    int numOfAsteroids;
};
