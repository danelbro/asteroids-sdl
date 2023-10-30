#include "../inc/TitleScreen.hpp"

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Box.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Stage.hpp"
#include "../inc/TextObject.hpp"
#include "../inc/utility.hpp"

static constexpr int title_font_size{ 72 };
static constexpr int instruction_font_size{ 36 };
static const std::string font_path{ "data/Play-Regular.ttf" };

static std::vector<TextObject> makeInstructions( GameWorld& gw,
                                                 TTF_Font* font,
                                                 SdlColor color,
                                                 SDL_Renderer* rend)
{
    const std::vector<std::string> insText{
        { "Enter to begin. ESC to quit." },
        { "Space to fire. L/R to turn." },
        { "Up to thrust. L-Shift to warp." }
    };
    constexpr double padding{ 150.0 };

    std::vector<TextObject> instructions{};

    for (size_t i{ 0 }; i < insText.size(); ++i) {
        instructions.push_back(TextObject{gw, {}, font, color, rend});
        instructions[i].updateText(insText[i], rend);
        double xpos{ (gw.screen.w / 2.0) - (instructions[i].size().x / 2.0) };
        double ypos{ gw.screen.h - padding - (instructions[i].size().y
                                              * (insText.size() - i)) };
        instructions[i].setPos({ xpos, ypos });
    }

    return instructions;
}

TitleScreen::TitleScreen(Box screen, Uint32 windowID, SDL_Renderer* renderer)
    : Stage{ screen, windowID, renderer, utl::StageID::TITLE_SCREEN },
      gameWorld{ screen, 0.0 },
      title_font{ utl::createFont(font_path, title_font_size)},
      instruction_font{ utl::createFont(font_path, instruction_font_size)},
      title{ gameWorld, {}, title_font.get(), customCols::text_col,
        renderer },
      instructions{ makeInstructions(gameWorld, instruction_font.get(),
                                   customCols::text_col, renderer) }
{
    const std::string titleText{ "Asteroids" };

    title.updateText(titleText, renderer);
    const double title_xPos{ (screen.w / 2.0) - (title.size().x / 2.0) };
    const double title_yPos{ screen.h / 3.0 };
    title.setPos({title_xPos, title_yPos});

    SDL_SetRenderDrawColor(renderer, customCols::bg.r, customCols::bg.g,
        customCols::bg.b, customCols::bg.a);
}

utl::StageID TitleScreen::handle_input(double, double,
    std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(gameWorld, windowID(), key_state);

    if (key_state[utl::KeyFlag::K_ESCAPE] || key_state[utl::KeyFlag::QUIT])
        return utl::StageID::QUIT;

    if (key_state[utl::KeyFlag::K_ENTER])
        return utl::StageID::PLAYING;

    return utl::StageID::TITLE_SCREEN;
}

utl::StageID TitleScreen::update(double, double)
{
    return utl::StageID::TITLE_SCREEN;
}

void TitleScreen::render(double, double)
{
    SDL_RenderClear(renderer());
    title.render(renderer());
    for (auto& to : instructions)
        to.render(renderer());
    SDL_RenderPresent(renderer());
}
