#pragma once

#include <array>
#include <memory>
#include <random>
#include <vector>

#include <SDL.h>

#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

class GameOver : public Stage
{
public:
    GameOver(Box screen, Uint32 windowID, SDL_Renderer* renderer,
             std::vector<std::unique_ptr<PhysicsEntity>>& physEntities,
             int score);

    utl::StageID handle_input(double, double,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    utl::StageID update(double t, double dt) override;
    void render(double, double) override;

    GameWorld& gameworld() { return m_gameWorld; }
private:
    GameWorld m_gameWorld;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> m_titleFont;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> m_scoreFont;
    std::mt19937 m_rng;
    PhysicsManager m_physMan;
    ScoreManager m_scoreMan;
    int m_score;
    TextObject m_GameOverText;
    TextObject m_ScoreText;
};
