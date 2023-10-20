#pragma once

#include <array>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Box.hpp"
#include "FlagEnums.hpp"
#include "GameWorld.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

class TitleScreen : public Stage
{
public:
    TitleScreen(Box screen, Uint32 windowID, SDL_Renderer* renderer);

    StageID handle_input(double t, double dt,
        std::array<bool, KeyFlag::K_TOTAL>& key_state) override;
    StageID update(double, double) override;
    void render(double, double) override;
private:
    GameWorld gameWorld;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> title_font;
    std::unique_ptr<TTF_Font, utl::sdl_deleter> instruction_font;
    TextObject title;
    TextObject instructions;
};

