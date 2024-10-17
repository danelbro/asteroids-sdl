#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utl_Box.hpp>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>

class TitleScreen : public utl::Stage {
public:
    TitleScreen(utl::Box& screen, uint32_t windowID,
                utl::Renderer& renderer);

    std::string
    handle_input(double t, double dt,
                 std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) override;
    std::string update(double, double) override;
    void render(double, double) override;

    utl::GameWorld& gameworld() { return gameWorld; }

private:
    utl::GameWorld gameWorld;
    utl::Font title_font;
    utl::Font instruction_font;
    utl::TextObject title;
    std::vector<utl::TextObject> instructions;
};
