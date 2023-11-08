#include "StageManager.hpp"

#include <chrono>
#include <memory>
#include <stdexcept>

#include "GameOver.hpp"
#include "MainLevel.hpp"
#include "Stage.hpp"
#include "TitleScreen.hpp"
#include "utility.hpp"

StageManager::StageManager(utl::StageID first)
    : current{ utl::StageID::STAGES_TOTAL }, next{ first }
{
    std::fill(keyState.begin(), keyState.end(), false);

    stages[utl::StageID::TITLE_SCREEN] = nullptr;
    stages[utl::StageID::PLAYING] = nullptr;
    stages[utl::StageID::HIGH_SCORES] = nullptr;
}

void StageManager::add_stage(utl::StageID key, std::unique_ptr<Stage> new_stage)
{
    stages[key] = std::move(new_stage);
}

void StageManager::run()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;

    // Set up for main loop
    // Structure from http://gameprogrammingpatterns.com/game-loop.html

    bool isRunning{ true };

    double t{ 0.0 };
    const double dt{ 0.01 };

    auto currentTime{ high_resolution_clock::now() };
    double accumulator{ 0.0 };
    while (isRunning) {
        current = next;
        Stage* current_stage = stages[current].get();

        auto newTime{ high_resolution_clock::now() };
        auto frameTime{ duration<double>(newTime - currentTime) };
        currentTime = newTime;

        accumulator += frameTime.count();

        while (accumulator >= dt) {
            if (!current_stage)
                throw (std::runtime_error("no stage set!"));

            next = current_stage->handle_input(t, dt, keyState);

            if (next != current) {
                handle_stage_transition(current_stage);
                current_stage = nullptr;
                break;
            }

            next = current_stage->update(t, dt);

            if (next != current) {
                handle_stage_transition(current_stage);
                current_stage = nullptr;
                break;
            }

            accumulator -= dt;
            t += dt;
        }

        if (next == utl::StageID::QUIT)
            break;

        if (current_stage)
            current_stage->render(t, dt);
    }
}

void StageManager::handle_stage_transition(Stage* current_stage)
{
    TitleScreen* tsptr{ nullptr };
    MainLevel* mlptr{ nullptr };
    GameOver* goptr{ nullptr };

    Box screen{};
    switch(current_stage->ID()) {
    case utl::StageID::TITLE_SCREEN:
        tsptr = dynamic_cast<TitleScreen*>(current_stage);
        if (!tsptr) throw std::runtime_error("buhhh");
        screen = tsptr->gameworld().screen;
        break;
    case utl::StageID::PLAYING:
        mlptr = dynamic_cast<MainLevel*>(current_stage);
        if (!mlptr) throw std::runtime_error("buhhh");
        screen = mlptr->gameworld().screen;
        break;
    case utl::StageID::HIGH_SCORES:
        goptr = dynamic_cast<GameOver*>(current_stage);
        if (!goptr) throw std::runtime_error("buhhh");
        screen = goptr->gameworld().screen;
        break;
    default:
        break;
    }

    auto windowID{ current_stage->windowID() };
    auto renderer{ current_stage->renderer() };

    keyState.fill(false);

    switch (next) {
    case utl::StageID::TITLE_SCREEN:
    {
        add_stage(next,
            std::make_unique<TitleScreen>(screen, windowID, renderer));
        break;
    }
    case utl::StageID::PLAYING:
        add_stage(next,
            std::make_unique<MainLevel>(screen, windowID, renderer));
        break;
    case utl::StageID::HIGH_SCORES:
    {
        if (!mlptr)
            throw std::runtime_error(
                "Trying to enter game over screen without playing");

        add_stage(next,
                  std::make_unique<GameOver>(screen, windowID, renderer,
                                             mlptr->physMan().physEntities,
                                             mlptr->scoreMan().score));
        break;
    }
    case utl::StageID::QUIT:
        next = utl::StageID::QUIT;
        break;
    default:
        throw std::runtime_error("bad stage");
    }

    stages[current].reset(nullptr);
}
