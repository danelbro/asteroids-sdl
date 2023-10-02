#include "../inc/ScoreManager.hpp"

#include <string>

#include <SDL.h>

#include "../inc/Colors.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/TextObject.hpp"

ScoreManager::ScoreManager(GameWorld* gw, Vec2d pos, TTF_Font* font, SDL_Renderer* renderer)
    : score{ 0 },
      scoreboard{ gw, pos, font, customCols::text_col },
      scoreText{ gw, pos, font, customCols::text_col },
      textObjects{}, m_renderer{ renderer }
{
    scoreboard.updateText("Score: ", m_renderer);
    textObjects.push_back(&scoreboard);

    scoreText.pos() = {pos.x + scoreboard.size().x, pos.y};
    scoreText.updateText(std::to_string(score), m_renderer);
    textObjects.push_back(&scoreText);
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
        scoreText.updateText(std::to_string(score), m_renderer);
        changed = false;
    }
}
