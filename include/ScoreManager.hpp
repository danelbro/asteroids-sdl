#pragma once

#include "utl_GameWorld.hpp"
#include "utl_SDLInterface.hpp"
#include "utl_TextObject.hpp"

#include <vector>

class ScoreManager {
public:
    ScoreManager(utl::Renderer& rend)
        : score{0}, lives{0}, textObjects{}, m_renderer{rend}
    {}

    // scoreboard_pos = top left
    ScoreManager(utl::GameWorld& gw, const utl::Vec2d& scoreboard_pos,
                 utl::Font& font, utl::Renderer& renderer, int playerLives);

    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    ScoreManager(ScoreManager&&) = default;
    ScoreManager& operator=(ScoreManager&&) = delete;
    ~ScoreManager() = default;

    void update_score(int add_this);
    void update_lives(int add_this);
    void refresh();

    int score;
    int lives;
    std::vector<utl::TextObject> textObjects;
    utl::Renderer& m_renderer;
    bool changed{false};
};
