#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <random>
#include <string>

#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"
#include "SDL_Interface.hpp"
#include "Stage.hpp"
#include "utility.hpp"

struct Box;

class Player;

class MainLevel : public Stage {
public:
    MainLevel(const Box& screen, uint32_t windowID, utl::Renderer& renderer);

    MainLevel(const MainLevel&) = delete;
    MainLevel& operator=(const MainLevel&) = delete;
    ~MainLevel() = default;

    std::string handle_input(double t, double dt,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    std::string update(double t, double dt) override;
    void render(double t, double dt) override;

    PhysicsManager& physMan() { return physicsManager; }
    ScoreManager& scoreMan() { return scoreManager; }
    GameWorld& gameworld() { return gameWorld; }
private:
    utl::Font font;
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
