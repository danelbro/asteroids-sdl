#include "TitleScreen.hpp"

#include <array>
#include <memory>
#include <string>
#include <vector>

#include "Box.hpp"
#include "Colors.hpp"
#include "flags.hpp"
#include "GameWorld.hpp"
#include "SDL_Interface.hpp"
#include "Stage.hpp"
#include "TextObject.hpp"
#include "utility.hpp"

static constexpr int title_font_size{ 72 };
static constexpr int instruction_font_size{ 36 };
static constexpr double padding{ 150.0 };
static const std::string font_path{ "data/Play-Regular.ttf" };

static std::vector<TextObject> makeInstructions( GameWorld& gw,
                                                 utl::Font& font,
                                                 const utl::Colour& color,
                                                 utl::Renderer& rend)
{
    const std::vector<std::string> insText{
        { "Enter to begin. ESC to quit." },
        { "Space to fire. L/R to turn." },
        { "Up to thrust. L-Shift to warp." }
    };

    std::vector<TextObject> instructions{};
    instructions.reserve(insText.size());

    for (size_t i{ 0 }; i < insText.size(); ++i) {
        instructions.emplace_back(TextObject{gw, {}, font, color, rend});
        instructions[i].updateText(insText[i]);
        double xpos{ (gw.screen.w / 2.0) - (instructions[i].size().x / 2.0) };
        double ypos{ gw.screen.h - padding - (instructions[i].size().y
                                              * (insText.size() - i)) };
        instructions[i].setPos({ xpos, ypos });
    }

    return instructions;
}

TitleScreen::TitleScreen(const Box& screen, uint32_t windowID,
    utl::Renderer& renderer)
    : Stage{ screen, windowID, renderer, utl::stageMap[utl::StageID::TITLE_SCREEN] },
      gameWorld{ screen, 0.0 },
      title_font{ utl::createFont(font_path, title_font_size)},
      instruction_font{ utl::createFont(font_path, instruction_font_size)},
      title{ gameWorld, {}, title_font, utl::customCols::text_col,
        renderer },
      instructions{ makeInstructions(gameWorld, instruction_font,
                                     utl::customCols::text_col, renderer) }
{
    const std::string titleText{ "Asteroids" };

    title.updateText(titleText);
    const double title_xPos{
        (gameWorld.screen.w / 2.0) - (title.size().x / 2.0)
    };
    const double title_yPos{ gameWorld.screen.h / 3.0 };
    title.setPos({title_xPos, title_yPos});

    utl::setRendererDrawColour(renderer, utl::customCols::bg);
}

static void reset_title(TextObject& title)
{
    title.setPos({
            title.gameWorld.screen.w / 2.0 - title.size().x / 2.0,
            title.gameWorld.screen.h / 3.0
        });
}

static void reset_instructions(std::vector<TextObject>& instructions)
{
    for (size_t i{ 0 }; i < instructions.size(); ++i) {
        instructions[i].setPos({
            (instructions[i].gameWorld.screen.w / 2.0)
            - (instructions[i].size().x / 2.0),
            instructions[i].gameWorld.screen.h - padding
            - (instructions[i].size().y * (instructions.size() - i))
            });
    }
}

std::string TitleScreen::handle_input(double, double,
    std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(gameWorld, windowID(), key_state);

    if (key_state[utl::KeyFlag::K_ESCAPE] || key_state[utl::KeyFlag::QUIT])
        return utl::stageMap[utl::StageID::QUIT];

    if (key_state[utl::KeyFlag::WINDOW_CHANGE]) {
        reset_title(title);
        reset_instructions(instructions);
    }

    if (key_state[utl::KeyFlag::K_ENTER])
        return utl::stageMap[utl::StageID::PLAYING];

    return utl::stageMap[utl::StageID::TITLE_SCREEN];
}

std::string TitleScreen::update(double, double)
{
    return utl::stageMap[utl::StageID::TITLE_SCREEN];
}

void TitleScreen::render(double, double)
{
    utl::clearScreen(renderer());
    title.render(renderer());
    for (auto& to : instructions)
        to.render(renderer());
    utl::presentRenderer(renderer());
}
