#include "../inc/TextObject.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Entity.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/utility.hpp"
#include "../inc/Vec2d.hpp"

TextObject::TextObject(GameWorld& gw, Vec2d pos, TTF_Font* font,
    SdlColor color, SDL_Renderer* rend)
    : Entity{ utl::EntityFlag::TEXT, gw, pos,
    std::vector<Vec2d>{}, color, 1.0 },
      text{ }, m_texture{ nullptr }, m_font{ font }, m_size{ 0, 0 },
      m_rend{ rend }
{}

void TextObject::free()
{
    m_texture.reset(nullptr);
    m_size = { 0, 0 };
}

void TextObject::loadFromRenderedText(std::string textureText,
                                      SDL_Color text_colour,
                                      SDL_Renderer* renderer)
{
    free();

    auto texPstruct{ utl::createTextTexture(m_font, textureText,
        text_colour, renderer) };

    m_texture = std::move(texPstruct.texP);
    m_size.x = texPstruct.w;
    m_size.y = texPstruct.h;
}

void TextObject::updateText(std::string new_text, SDL_Renderer* renderer)
{
    text = new_text;
    loadFromRenderedText(
        text,
        { m_color.r, m_color.g, m_color.b, m_color.a },
        renderer
    );
}

void TextObject::render(SDL_Renderer* renderer)
{
    SDL_Rect renderQuad = { static_cast<int>(m_pos.x),
                            static_cast<int>(m_pos.y),
                            static_cast<int>(m_size.x),
                            static_cast<int>(m_size.y) };
    SDL_RenderCopy(renderer, m_texture.get(), nullptr, &renderQuad);
}
