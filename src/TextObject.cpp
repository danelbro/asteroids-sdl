#include "../inc/TextObject.hpp"

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

TextObject::TextObject(GameWorld *gw, Vec2d pos, TTF_Font* font, SdlColor color,
                       SDL_Renderer* rend)
    : Entity{ EntityFlag::TEXT, gw, pos, std::vector<Vec2d>{}, color, 1.0 },
      text{ }, m_texture{ nullptr }, m_font{ font }, m_size{ 0, 0 },
      m_rend{ rend }
{}

TextObject::TextObject(const TextObject& to)
    : Entity{ EntityFlag::TEXT, to.gameWorld, to.m_pos, to.m_shape,
              to.m_color, to.m_scale }, text{ to.text }, m_texture{ nullptr },
      m_font{ to.m_font }, m_size{ to.m_size }, m_rend{ to.m_rend }
{
    updateText(text, m_rend);
}

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

bool TextObject::loadFromRenderedText(std::string textureText,
                                      SDL_Color text_colour,
                                      SDL_Renderer* renderer)
{
    free();

    SDL_Surface* textSurface = TTF_RenderUTF8_Blended(m_font,
                                                      textureText.c_str(),
                                                      text_colour);
    if (!textSurface)
        throw SdlException(std::string{
                "Could not create textSurface! SDL_Error: ",
                SDL_GetError()});
    else
    {
        m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!m_texture)
            throw SdlException(std::string{
                    "Could not create texture from textSurface! SDL_Error: ",
                    SDL_GetError()});
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
    text = new_text;
    if (!loadFromRenderedText(text, { m_color.r, m_color.g,
                                      m_color.b, m_color.a}, renderer))
        throw SdlException(
            std::string{"Could not update text! SDL_Error: ", SDL_GetError()});
}

void TextObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad = { static_cast<int>(m_pos.x),
                            static_cast<int>(m_pos.y),
                            static_cast<int>(m_size.x),
                            static_cast<int>(m_size.y) };
    SDL_RenderCopy(renderer, m_texture, nullptr, &renderQuad);
}
