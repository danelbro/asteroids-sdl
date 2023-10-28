#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameWorld.hpp"
#include "TextObject.hpp"

class ScoreManager
{
public:
    ScoreManager()
        : score{ 0 }, lives{ 0 }, textObjects{ }, m_renderer{ nullptr }
        {}

    // scoreboard_pos = top left
    ScoreManager(GameWorld &gw, Vec2d scoreboard_pos, TTF_Font *font,
                 SDL_Renderer *renderer, int playerLives);

    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;
    ScoreManager(ScoreManager&&) = default;
    ScoreManager& operator=(ScoreManager&&) = default;
    ~ScoreManager() = default;

    void update_score(int add_this);
    void update_lives(int add_this);
    void refresh();

    int score;
    int lives;
    std::vector<TextObject> textObjects;
    SDL_Renderer* m_renderer;
    bool changed{ false };
};

