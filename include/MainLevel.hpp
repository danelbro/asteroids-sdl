#pragma once

#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <utl_Box.hpp>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>

class Player;

class MainLevel : public utl::Stage {
public:
    MainLevel(utl::Box& screen, uint32_t windowID,
              utl::Renderer& renderer);

    MainLevel(const MainLevel&) = delete;
    MainLevel& operator=(const MainLevel&) = delete;
    ~MainLevel() = default;

    std::string
    handle_input(double t, double dt,
                 std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    std::string update(double t, double dt) override;
    void render(double t, double dt) override;

    PhysicsManager& physMan() { return physicsManager; }
    ScoreManager& scoreMan() { return scoreManager; }
    utl::GameWorld& gameworld() { return gameWorld; }

private:
    utl::Font font;
    utl::GameWorld gameWorld;
    std::mt19937 rng;
    PhysicsManager physicsManager;
    Player& player;
    ScoreManager scoreManager;
    bool asteroidsRemain;
    int numOfAsteroids;
    bool enemiesRemain;
    double levelElapsedTime;
};
