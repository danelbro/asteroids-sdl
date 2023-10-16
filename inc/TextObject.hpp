#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Colors.hpp"
#include "Entity.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"

class TextObject : public Entity
{
public:
    TextObject()
        : Entity{EntityFlag::E_TYPE_TOTAL, {}, {}, {}, {}, 1.0},
          text{ }, m_texture{ nullptr }, m_font{ nullptr }, m_size{ }
        {}

    TextObject(GameWorld* gw, Vec2d pos, TTF_Font* font, SdlColor color,
               SDL_Renderer* rend);

    ~TextObject();
    TextObject(const TextObject&);

    friend void swap(TextObject& first, TextObject& second) {
        using std::swap;

        swap(first.text, second.text);
        swap(first.m_texture, second.m_texture);
        swap(first.m_font, second.m_font);
        swap(first.m_size, second.m_size);
        swap(first.m_rend, second.m_rend);
    }

    TextObject& operator=(TextObject other) {
        swap(*this, other);

        return *this;
    }

    bool loadFromRenderedText(std::string textureText, SDL_Color text_colour,
        SDL_Renderer* renderer);

    void free();

    void render(SDL_Renderer* renderer);

    void updateText(std::string new_text, SDL_Renderer* renderer);
    void update(double, double) {}

    const Vec2d size() { return m_size; }

private:
    std::string text;
    SDL_Texture* m_texture;
    TTF_Font* m_font;
    Vec2d m_size;
    SDL_Renderer* m_rend = nullptr;
};

