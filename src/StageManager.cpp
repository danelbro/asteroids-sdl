#include "../inc/StageManager.hpp"

#include <chrono>
#include <memory>

#include "../inc/FlagEnums.hpp"
#include "../inc/MainLevel.hpp"
#include "../inc/Stage.hpp"
#include "../inc/TitleScreen.hpp"
#include "../inc/utility.hpp"

StageManager::StageManager()
{
    std::fill(keyState.begin(), keyState.end(), false);

    stages[StageID::TITLE_SCREEN] = nullptr;
    stages[StageID::PLAYING] = nullptr;
    stages[StageID::HIGH_SCORES] = nullptr;
}

void StageManager::add_stage(StageID key, std::unique_ptr<Stage> new_stage)
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
                handle_stage_transition();
                current_stage = nullptr;
                break;
            }

            next = current_stage->update(t, dt);

            if (next != current) {
                handle_stage_transition();
                current_stage = nullptr;
                break;
            }

            accumulator -= dt;
            t += dt;
        }

        if (next == StageID::QUIT)
            break;

        if (current_stage)
            current_stage->render(t, dt);
    }
}

bool StageManager::handle_stage_transition()
{
    if (next != current) {
        keyState.fill(false);

        switch (next) {
        case StageID::TITLE_SCREEN:
            stages.erase(next);
            add_stage(next, std::make_unique<TitleScreen>(
                stages[current]->screen(),
                stages[current]->windowID(),
                stages[current]->renderer()));
            stages.erase(current);
            break;
        case StageID::PLAYING:
            stages.erase(next);
            add_stage(next, std::make_unique<MainLevel>(
                stages[current]->screen(),
                stages[current]->windowID(),
                stages[current]->renderer()));
            stages.erase(current);
            break;
        case StageID::HIGH_SCORES:
            // remove later
            next = StageID::TITLE_SCREEN;
            stages.erase(next);
            add_stage(next, std::make_unique<TitleScreen>(
                stages[current]->screen(),
                stages[current]->windowID(),
                stages[current]->renderer()));
            stages.erase(current);
            break;
        case StageID::QUIT:
            next = StageID::QUIT;
            break;
        default:
            throw std::runtime_error("bad stage");
        }
        return false;
    }

    return true;
}
