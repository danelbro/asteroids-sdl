#include "../inc/TitleScreen.hpp"

#include <array>
#include <memory>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "../inc/Box.hpp"
#include "../inc/FlagEnums.hpp"
#include "../inc/GameLoop.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Stage.hpp"
#include "../inc/TextObject.hpp"
#include "../inc/utility.hpp"

static constexpr int title_font_size{ 72 };
static constexpr int instruction_font_size{ 36 };
static const std::string font_path{ "data/Play-Regular.ttf" };

TitleScreen::TitleScreen(Box screen, Uint32 windowID, SDL_Renderer* renderer)
    : Stage{ screen, windowID, renderer }, gameWorld{ screen, 0.0 },
    title_font{ utl::createFont(font_path, title_font_size)},
    instruction_font{ utl::createFont(font_path, instruction_font_size)},
    title{ gameWorld, {}, title_font.get(), customCols::text_col,
        renderer },
    instructions{ gameWorld, {}, instruction_font.get(),
        customCols::text_col, renderer }
{
    const double padding{ 100 };

    title.updateText("Asteroids", renderer);
    const double title_xPos{ (screen.w / 2.0) - (title.size().x / 2.0) };
    const double title_yPos{ screen.h / 3.0 };
    title.setPos({title_xPos, title_yPos});

    instructions.updateText("Space to begin. ESC to quit.", renderer);
    const double ins_xPos{(screen.w / 2.0) - (instructions.size().x / 2.0)};
    const double ins_yPos{ title_yPos + title.size().y + padding};
    instructions.setPos({ins_xPos, ins_yPos});

    SDL_SetRenderDrawColor(renderer, customCols::bg.r, customCols::bg.g,
        customCols::bg.b, customCols::bg.a);
}

StageID TitleScreen::handle_input(double, double,
    std::array<bool, KeyFlag::K_TOTAL>& key_state)
{
    GameLoop::process_input(gameWorld, windowID(), key_state);

    if (key_state[KeyFlag::K_ESCAPE] || key_state[KeyFlag::QUIT])
        return StageID::QUIT;

    if (key_state[KeyFlag::K_SPACE])
        return StageID::PLAYING;

    return StageID::TITLE_SCREEN;
}

StageID TitleScreen::update(double, double)
{
    return StageID::TITLE_SCREEN;
}

void TitleScreen::render(double, double)
{
    SDL_RenderClear(renderer());
    title.render(renderer());
    instructions.render(renderer());
    SDL_RenderPresent(renderer());
}