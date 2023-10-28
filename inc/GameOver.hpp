#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "FlagEnums.hpp"
#include "GameWorld.hpp"
#include "PhysicsComponent.hpp"
#include "PhysicsEntity.hpp"
#include "PhysicsManager.hpp"
#include "Ship.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

class GameOver : public Stage
{
public:
    GameOver(Box screen, Uint32 windowID, SDL_Renderer* renderer,
             std::vector<std::unique_ptr<PhysicsEntity>>& physEntities,
             std::vector<std::unique_ptr<PhysicsComponent>>& physComs,
             int score);

    StageID handle_input(double, double,
        std::array<bool, KeyFlag::K_TOTAL>& key_state) override;
    StageID update(double t, double dt) override;
    void render(double, double) override;
private:
    GameWorld m_gameWorld;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> m_titleFont;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> m_scoreFont;
    PhysicsManager m_physMan;
    ScoreManager m_scoreMan;
    int m_score;
    TextObject m_GameOverText;
    TextObject m_ScoreText;
    std::mt19937 m_rng;
};
