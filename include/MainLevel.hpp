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
    MainLevel(utl::Box& screen, uint32_t windowID, utl::Renderer& renderer);

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
    void check_targets_cleared();
    void tick_enemy_timer(const double& dt);
    void spawn_enemy(const double& enemyTime);
    void progress_level();
    void update_physics(const double& dt);
    void update_entities(const double& t, const double& dt);
    void update_scoreboard_lives();
    std::string check_game_over();

    void render_entities();
    void render_text();

    utl::Font font;
    utl::GameWorld gameWorld;
    std::mt19937 rng;
    PhysicsManager physicsManager;
    Player& player;
    ScoreManager scoreManager;
    bool areAsteroidsRemaining;
    int numOfAsteroids;
    bool areEnemiesRemaining;
    double enemyTimer;
};
