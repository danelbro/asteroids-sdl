#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Entity.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"

class TextObject : public Entity
{
public:
    TextObject(GameWorld* gw, Vec2d pos, TTF_Font* font, SdlColor color);
    ~TextObject();

    bool loadFromRenderedText(std::string textureText, SDL_Color text_colour,
        SDL_Renderer* renderer);

    void free();

    void render(SDL_Renderer* renderer);

    void updateText(std::string new_text, SDL_Renderer* renderer);
    void update(double, double) {}

    const Vec2d size() { return m_size; }
private:
    SDL_Texture* m_texture;
    TTF_Font* m_font;
    Vec2d m_size;
};

