#include "../inc/ScoreManager.hpp"

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/TextObject.hpp"

ScoreManager::ScoreManager(GameWorld& gw, Vec2d pos, TTF_Font* font,
    SDL_Renderer* renderer)
    : score{ 0 }, textObjects{}, m_renderer{ renderer }

{
    textObjects.push_back(
        std::make_unique<TextObject>(gw, pos, font, customCols::text_col, renderer));
    textObjects[0]->updateText("Score: ", m_renderer);

    textObjects.push_back(
        std::make_unique<TextObject>(gw, pos, font, customCols::text_col, renderer));
    textObjects[1]->pos() = { pos.x + textObjects[0]->size().x, pos.y};
    textObjects[1]->updateText(std::to_string(score), m_renderer);
}

void ScoreManager::update_score(int add_this)
{
    score += add_this;
    if (score < 0) score = 0;
    changed = true;
}

void ScoreManager::refresh()
{
    if (changed) {
        textObjects[1]->updateText(std::to_string(score), m_renderer);
        changed = false;
    }
}
