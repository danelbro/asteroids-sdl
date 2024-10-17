#include "ScoreManager.hpp"

#include "Colors.hpp"

#include <string>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_TextObject.hpp>

ScoreManager::ScoreManager(utl::GameWorld& gw, const utl::Vec2d& pos,
                           utl::Font& font, utl::Renderer& renderer,
                           int playerLives)
    : score{0}, lives{playerLives}, textObjects{}, m_renderer{renderer}

{
    textObjects.push_back(utl::TextObject{gw.screen, pos, font,
                                          customCols::text_col, m_renderer});
    textObjects[0].updateText("Score: ");

    textObjects.push_back(
        utl::TextObject{gw.screen,
                        {pos.x + textObjects[0].size().x, pos.y},
                        font,
                        customCols::text_col,
                        renderer});
    textObjects[1].updateText(std::to_string(score));

    textObjects.push_back(
        utl::TextObject{gw.screen,
                        {pos.x, pos.y + textObjects[0].size().y},
                        font,
                        customCols::text_col,
                        renderer});
    textObjects[2].updateText("Lives: ");

    textObjects.push_back(utl::TextObject{
        gw.screen,
        {pos.x + textObjects[2].size().x, textObjects[2].pos().y},
        font,
        customCols::text_col,
        renderer});
    textObjects[3].updateText(std::to_string(lives));
}

void ScoreManager::update_score(int add_this)
{
    score += add_this;
    if (score < 0)
        score = 0;
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
