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
        : Entity{EntityFlag::E_TYPE_TOTAL, {}, {}, {}, {}, 1.0},
        text{ }, m_texture{ nullptr }, m_font{ nullptr }, m_size{ }, 
        m_rend{ nullptr }
        {}

    TextObject(GameWorld* gw, Vec2d pos, TTF_Font* font, SdlColor color,
               SDL_Renderer* rend);

    void loadFromRenderedText(std::string textureText, SDL_Color text_colour,
        SDL_Renderer* renderer);

    void free();

    void render(SDL_Renderer* renderer);

    void updateText(std::string new_text, SDL_Renderer* renderer);
    void update(double, double) {}

    const Vec2d size() { return m_size; }

private:
    std::string text;
    std::unique_ptr<SDL_Texture, sdl_deleter> m_texture;
    TTF_Font* m_font;
    Vec2d m_size;
    SDL_Renderer* m_rend;
};

