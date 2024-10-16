﻿#pragma once

#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"

#include <array>
#include <cstdint>
#include <memory>
#include <random>
#include <string>
#include <utl_Box.hpp>
#include <utl_GameWorld.hpp>
#include <utl_PhysicsEntity.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <vector>

class GameOver : public utl::Stage {
public:
    GameOver(
        const utl::Box& screen, uint32_t windowID, utl::Renderer& renderer,
        const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
        int score);

    std::string
    handle_input(double, double,
                 std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    std::string update(double t, double dt) override;
    void render(double, double) override;

    utl::GameWorld& gameworld() { return m_gameWorld; }

private:
    utl::GameWorld m_gameWorld;
    utl::Font m_titleFont;
    utl::Font m_scoreFont;
    std::mt19937 m_rng;
    PhysicsManager m_physMan;
    ScoreManager m_scoreMan;
    int m_score;
    utl::TextObject m_GameOverText;
    utl::TextObject m_ScoreText;
};