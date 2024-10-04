#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "SDL_Interface.hpp"
#include "ScoreManager.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"

struct Box;

class PhysicsEntity;

class GameOver : public Stage
{
public:
    GameOver(const Box& screen, uint32_t windowID, utl::Renderer& renderer,
             const std::vector<std::unique_ptr<PhysicsEntity>>& physEntities,
             int score);

    std::string handle_input(double, double,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    std::string update(double t, double dt) override;
    void render(double, double) override;

    GameWorld& gameworld() { return m_gameWorld; }
private:
    GameWorld m_gameWorld;
    utl::Font m_titleFont;
    utl::Font m_scoreFont;
    std::mt19937 m_rng;
    PhysicsManager m_physMan;
    ScoreManager m_scoreMan;
    int m_score;
    TextObject m_GameOverText;
    TextObject m_ScoreText;
};
