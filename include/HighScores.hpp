#pragma once

#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <utl_Box.hpp>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_ScoreBoard.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <utl_random.hpp>
#include <vector>

struct NewHighScore {
    NewHighScore(bool isNewHS, int newPos)
        : isNewHighScore{isNewHS}, newHighScorePos{newPos}
    {}
    bool isNewHighScore;
    int newHighScorePos;
};

class HighScores : public utl::Stage {
public:
    HighScores(
        utl::Box& screen, uint32_t windowID, utl::Renderer& renderer,
        utl::RNG& rng,
        const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
        int score);

    std::string
    handle_input(double t, double dt,
                 std::array<bool, utl::KeyFlag::K_TOTAL>& keyState) override;
    std::string update(double t, double dt) override;
    void render(double t, double dt) override;

    void check_asteroids_cleared();
    void stop_enemy_firing();

    void read_high_scores(std::vector<std::string>& highScores,
                          const std::filesystem::path& path);
    NewHighScore calculate_high_scores(const int& score,
                                       std::vector<std::string>& highScores);
    void write_high_scores(const std::vector<std::string>& highScores,
                           const std::filesystem::path& path);

private:
    utl::GameWorld m_gameWorld;
    utl::Font titleFont;
    utl::Font scoreFont;
    utl::RNG& m_rng;
    PhysicsManager m_physMan;
    ScoreManager m_scoreMan;
    int m_score;
    utl::TextObject m_highScoreTitle;
    bool asteroidsRemain;
    utl::ScoreBoard m_scoreBoard;
};
