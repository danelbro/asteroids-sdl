#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "FlagEnums.hpp"

class Entity;
class PhysicsComponent;
class Player;

bool processInput(GameWorld *GameWorld, Player *player, double dt, 
    std::array<bool, K_TOTAL> &key_state, EntityManager *entMan);

bool handleInput(std::array<bool, K_TOTAL> &key_state);

void updateAll(std::vector<std::unique_ptr<PhysicsComponent>> &physicsManager,
               double t, double dt);

void render(std::vector<std::shared_ptr<Entity>> &entities,
            SDL_Renderer *renderer);
