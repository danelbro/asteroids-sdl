#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "KeyFlag.hpp"

class Entity;
class PhysicsComponent;
class Player;

bool processInput(Player *player, std::array<bool, K_TOTAL> &key_state);

bool handleInput(std::array<bool, K_TOTAL> &key_state);

void updateAll(std::vector<std::unique_ptr<PhysicsComponent>> &physicsManager);

void render(std::vector<std::shared_ptr<Entity>> &entities,
            SDL_Renderer *renderer);
