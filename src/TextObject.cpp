#include "../inc/TextObject.hpp"

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

TextObject::TextObject(GameWorld *gw, Vec2d pos, TTF_Font* font, SdlColor color)
    : Entity{ EntityFlag::TEXT, gw, pos, std::vector<Vec2d>{}, color, 1.0 },
    m_texture{ nullptr }, m_font{ font }, m_size{ 0, 0 }
{}

TextObject::~TextObject()
{
    free();
}

void TextObject::free()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_size = { 0, 0 };
    }
}

bool TextObject::loadFromRenderedText(std::string textureText, SDL_Color text_colour,
    SDL_Renderer* renderer)
{
    free();

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(m_font, textureText.c_str(), text_colour);
    if (!textSurface)
        throw SdlException();
    else
    {
        m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!m_texture)
            throw SdlException();
        else
        {
            m_size.x = textSurface->w;
            m_size.y = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return m_texture != nullptr;
}

void TextObject::updateText(std::string new_text, SDL_Renderer* renderer)
{
    if (!loadFromRenderedText(new_text, { m_color.r, m_color.g, m_color.b, m_color.a}, renderer))
        throw SdlException();
}

void TextObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad = { static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
        static_cast<int>(m_size.x), static_cast<int>(m_size.y) };
    SDL_RenderCopy(renderer, m_texture, nullptr, &renderQuad);
}
