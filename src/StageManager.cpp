#include "../inc/StageManager.hpp"

void StageManager::add_stage(StageID key, Stage& new_stage)
{
}

void StageManager::run()
{
    Stage& current_stage = stages[current];
    StageID next = current;

    next = current_stage.handle_input();
    if (next != current) {
        current = next;
        stages[current].init();
        return;
    }

    next = current_stage.update();
    if (next != current) {
        current = next;
        stages[current].init();
        return;
    }

    current_stage.render();
}
