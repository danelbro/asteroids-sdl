#include "../inc/StageManager.hpp"

#include <chrono>

#include "../inc/FlagEnums.hpp"
#include "../inc/MainLevel.hpp"
#include "../inc/Stage.hpp"
#include "../inc/utility.hpp"

StageManager::StageManager()
{
    std::fill(keyState.begin(), keyState.end(), false);

    stages[StageID::TITLE_SCREEN] = nullptr;
    stages[StageID::PLAYING] = nullptr;
    stages[StageID::HIGH_SCORES] = nullptr;
}

void StageManager::add_stage(StageID key, Stage* new_stage)
{
    stages[key] = new_stage;
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
        Stage* current_stage = stages[current];

        auto newTime{ high_resolution_clock::now() };
        auto frameTime{ duration<double>(newTime - currentTime) };
        currentTime = newTime;

        accumulator += frameTime.count();

        while (accumulator >= dt) {
            next = current_stage->handle_input(t, dt, keyState);

            if (next != current) {
                handle_stage_transition();
                break;
            }

            next = current_stage->update(t, dt);
            if (next != current) {
                handle_stage_transition();
                break;
            }

            accumulator -= dt;
            t += dt;
        }

        if(handle_stage_transition())
            current_stage->render(t, dt);
    }
}

bool StageManager::handle_stage_transition()
{
    if (next != current) {
        switch (next) {
        case StageID::TITLE_SCREEN:
            // remove later
            next = StageID::PLAYING;
            break;
        case StageID::PLAYING:
            delete stages[next];
            add_stage(next, new MainLevel{stages[current]->screen(),
                                          stages[current]->windowID(),
                                          stages[current]->renderer()});
            break;
        case StageID::HIGH_SCORES:
            // remove later
            next = StageID::PLAYING;
            break;
        default:
            throw SdlException("bad stage");
        }
        current = next;
        return false;
    }

    return true;
}
