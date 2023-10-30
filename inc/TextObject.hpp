#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Colors.hpp"
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"
#include "utility.hpp"

class TextObject : public Entity
{
public:
    TextObject()
        : Entity{ utl::EntityFlag::E_TYPE_TOTAL, GameWorld{}, {}, {}, {}, 1.0 },
        text{ }, m_texture{ nullptr }, m_font{ nullptr }, m_size{ },
        m_rend{ nullptr }
        {}

    TextObject(GameWorld& gw, Vec2d pos, TTF_Font* font, SdlColor color,
               SDL_Renderer* rend);
    TextObject(const TextObject&) = delete;
    TextObject& operator=(const TextObject&) = delete;
    TextObject(TextObject&&) = default;
    TextObject& operator=(TextObject&&) = delete;
    ~TextObject() = default;

    void loadFromRenderedText(std::string textureText, SDL_Color text_colour,
        SDL_Renderer* renderer);

    void free();

    void render(SDL_Renderer* renderer);

    void updateText(std::string new_text, SDL_Renderer* renderer);
    void update(double, double) {}

    void setPos(Vec2d new_pos) { m_pos = new_pos; }

    const Vec2d size() { return m_size; }

private:
    std::string text;
    std::unique_ptr<SDL_Texture, utl::sdl_deleter> m_texture;
    TTF_Font* m_font;
    Vec2d m_size;
    SDL_Renderer* m_rend;
};

