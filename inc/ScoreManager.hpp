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
        : score{ 0 }, textObjects{ }, m_renderer{ nullptr }
        {}

    ScoreManager(GameWorld& gw, Vec2d scoreboard_pos, TTF_Font* font,
                 SDL_Renderer* renderer); // scoreboard_pos = top left

    void update_score(int add_this);
    void refresh();

    int score;
    std::vector<std::unique_ptr<TextObject>> textObjects;
    SDL_Renderer* m_renderer;
    bool changed{ false };
};

