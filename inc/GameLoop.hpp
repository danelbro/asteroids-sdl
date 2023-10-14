#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "FlagEnums.hpp"
#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"

class Entity;
class PhysicsComponent;
class Player;

bool processInput(GameWorld* GameWorld, Uint32 windowID, Player* player, double dt,
                  std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)>& key_state,
                  PhysicsManager* physMan);

bool handleInput(GameWorld* gw, Uint32 windowID,
                 std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)> &key_state);

bool updateAll(GameWorld* gw, EntityManager* entMan, PhysicsManager* physMan,
    ScoreManager* scoreMan, double t, double dt, std::mt19937& rng);

void render(EntityManager* entMan, PhysicsManager* physMan, ScoreManager* scoreMan,
            SDL_Renderer *renderer);
