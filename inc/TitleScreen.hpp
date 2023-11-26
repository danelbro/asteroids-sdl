#pragma once

#include <array>
#include <cstdint>
#include <memory>

#include "Box.hpp"
#include "GameWorld.hpp"
#include "SDL_Interface.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

class TitleScreen : public Stage
{
public:
    TitleScreen(const Box& screen, uint32_t windowID, utl::Renderer& renderer);

    utl::StageID handle_input(double t, double dt,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    utl::StageID update(double, double) override;
    void render(double, double) override;

    GameWorld& gameworld() { return gameWorld; }
private:
    GameWorld gameWorld;
    utl::Font title_font;
    utl::Font instruction_font;
    TextObject title;
    std::vector<TextObject> instructions;
};

