#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "DirFlag.hpp"
#include "Entity.hpp"

// Quit the game on certain inputs
bool handleInput(std::vector<std::unique_ptr<Entity>> &entities,
                 std::array<bool, K_TOTAL> &key_state);

void updateAll(std::vector<std::unique_ptr<Entity>> &entities,
               std::array<bool, K_TOTAL> key_state);

void render(std::vector<std::unique_ptr<Entity>> &entities,
            SDL_Renderer *renderer, double progress);
