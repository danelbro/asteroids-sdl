#pragma once

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameWorld.hpp"
#include "TextObject.hpp"

class ScoreManager
{
public:
    ScoreManager(GameWorld* gw, Vec2d scoreboard_pos, TTF_Font* font, SDL_Renderer* renderer); // scoreboard_pos = top left

    int score;
    TextObject scoreboard;
    TextObject scoreText;
    std::vector<TextObject*> textObjects;

    SDL_Renderer* m_renderer;

    bool changed{ false };

    void update_score(int add_this);
    void refresh();
};

