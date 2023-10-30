#include "../inc/ScoreManager.hpp"

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/TextObject.hpp"

ScoreManager::ScoreManager(GameWorld& gw, Vec2d pos, TTF_Font* font,
                           SDL_Renderer* renderer, int playerLives)
    : score{ 0 }, lives{ playerLives }, textObjects{}, m_renderer{ renderer }

{
    textObjects.push_back(TextObject{gw, pos, font, customCols::text_col,
                                     renderer});
    textObjects[0].updateText("Score: ", m_renderer);

    textObjects.push_back(TextObject{gw, { pos.x + textObjects[0].size().x,
                                               pos.y},
                                     font, customCols::text_col, renderer});
    textObjects[1].updateText(std::to_string(score), m_renderer);

    textObjects.push_back(TextObject{gw, {pos.x,
                                              pos.y + textObjects[0].size().y},
                                     font, customCols::text_col, renderer});
    textObjects[2].updateText("Lives: ", m_renderer);

    textObjects.push_back(TextObject{gw, {pos.x + textObjects[2].size().x,
                                              textObjects[2].pos().y},
                                     font, customCols::text_col, renderer});
    textObjects[3].updateText(std::to_string(lives), renderer);
}

void ScoreManager::update_score(int add_this)
{
    score += add_this;
    if (score < 0) score = 0;
    changed = true;
}

void ScoreManager::update_lives(int add_this)
{
    lives += add_this;
    changed = true;
}

void ScoreManager::refresh()
{
    if (changed) {
        textObjects[1].updateText(std::to_string(score), m_renderer);
        textObjects[3].updateText(std::to_string(lives), m_renderer);
        changed = false;
    }
}
