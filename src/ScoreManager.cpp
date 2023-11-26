#include "ScoreManager.hpp"

#include <string>

#include "SDL_Interface.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "TextObject.hpp"

ScoreManager::ScoreManager(GameWorld& gw, const Vec2d& pos, utl::Font& font,
                           utl::Renderer& renderer, int playerLives)
    : score{ 0 }, lives{ playerLives }, textObjects{}, m_renderer{ renderer }

{
    textObjects.push_back(TextObject{gw, pos, font, utl::customCols::text_col,
                                     m_renderer});
    textObjects[0].updateText("Score: ");

    textObjects.push_back(TextObject{gw, { pos.x + textObjects[0].size().x,
                                               pos.y},
                                     font, utl::customCols::text_col,
                                     renderer});
    textObjects[1].updateText(std::to_string(score));

    textObjects.push_back(TextObject{gw, {pos.x,
                                              pos.y + textObjects[0].size().y},
                                     font, utl::customCols::text_col,
                                     renderer});
    textObjects[2].updateText("Lives: ");

    textObjects.push_back(TextObject{gw, {pos.x + textObjects[2].size().x,
                                              textObjects[2].pos().y},
                                     font, utl::customCols::text_col,
                                     renderer});
    textObjects[3].updateText(std::to_string(lives));
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
        textObjects[1].updateText(std::to_string(score));
        textObjects[3].updateText(std::to_string(lives));
        changed = false;
    }
}
