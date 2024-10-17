#include "TitleScreen.hpp"

#include "Colors.hpp"
#include "flags.hpp"

#include <array>
#include <string>
#include <utl_Box.hpp>
#include <utl_GameWorld.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_TextObject.hpp>
#include <utl_utility.hpp>
#include <vector>

static constexpr int title_font_size{72};
static constexpr int instruction_font_size{36};
static constexpr double padding{150.0};
static const std::string font_path{"data/Play-Regular.ttf"};

static std::vector<utl::TextObject> makeInstructions(utl::Box& screen,
                                                     utl::Font& font,
                                                     const utl::Colour& color,
                                                     utl::Renderer& rend)
{
    const std::vector<std::string> insText{{"Enter to begin. ESC to quit."},
                                           {"Space to fire. L/R to turn."},
                                           {"Up to thrust. L-Shift to warp."}};

    std::vector<utl::TextObject> instructions{};
    instructions.reserve(insText.size());

    for (size_t i{0}; i < insText.size(); ++i) {
        instructions.emplace_back(
            utl::TextObject{screen, {}, font, color, rend});
        instructions[i].updateText(insText[i]);
        double xpos{(screen.w / 2.0) - (instructions[i].size().x / 2.0)};
        double ypos{screen.h - padding
                    - (instructions[i].size().y * (insText.size() - i))};
        instructions[i].setPos({xpos, ypos});
    }

    return instructions;
}

TitleScreen::TitleScreen(utl::Box& screen, uint32_t windowID,
                         utl::Renderer& renderer)
    : Stage{screen, windowID, renderer, STAGE_MAP[STAGE_ID::TITLE_SCREEN]},
      gameWorld{screen, 0.0},
      title_font{utl::createFont(font_path, title_font_size)},
      instruction_font{utl::createFont(font_path, instruction_font_size)},
      title{gameWorld.screen, {}, title_font, customCols::text_col, renderer},
      instructions{makeInstructions(gameWorld.screen, instruction_font,
                                    customCols::text_col, renderer)}
{
    const std::string titleText{"Asteroids"};

    title.updateText(titleText);
    const double title_xPos{(gameWorld.screen.w / 2.0)
                            - (title.size().x / 2.0)};
    const double title_yPos{gameWorld.screen.h / 3.0};
    title.setPos({title_xPos, title_yPos});

    utl::setRendererDrawColour(renderer, customCols::bg);
}

static void reset_title(utl::TextObject& title)
{
    title.setPos({title.screen().w / 2.0 - title.size().x / 2.0,
                  title.screen().h / 3.0});
}

static void reset_instructions(std::vector<utl::TextObject>& instructions)
{
    for (size_t i{0}; i < instructions.size(); ++i) {
        instructions[i].setPos(
            {(instructions[i].screen().w / 2.0)
                 - (instructions[i].size().x / 2.0),
             instructions[i].screen().h - padding
                 - (instructions[i].size().y * (instructions.size() - i))});
    }
}

std::string
TitleScreen::handle_input(double, double,
                          std::array<bool, utl::KeyFlag::K_TOTAL>& key_state)
{
    utl::process_input(screen(), windowID(), key_state);

    if (key_state[utl::KeyFlag::K_ESCAPE] || key_state[utl::KeyFlag::QUIT])
        return STAGE_MAP[STAGE_ID::QUIT];

    if (key_state[utl::KeyFlag::WINDOW_CHANGE]) {
        gameWorld.screen = screen();
        reset_title(title);
        reset_instructions(instructions);
    }

    if (key_state[utl::KeyFlag::K_ENTER]) return STAGE_MAP[STAGE_ID::PLAYING];

    return STAGE_MAP[STAGE_ID::TITLE_SCREEN];
}

std::string TitleScreen::update(double, double)
{
    return STAGE_MAP[STAGE_ID::TITLE_SCREEN];
}

void TitleScreen::render(double, double)
{
    utl::clearScreen(renderer());
    title.render(renderer());
    for (auto& to : instructions) to.render(renderer());
    utl::presentRenderer(renderer());
}
