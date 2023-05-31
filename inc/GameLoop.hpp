#pragma once

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "FlagEnums.hpp"
#include "PhysicsManager.hpp"

struct GameWorld;
class Entity;
class PhysicsComponent;
class Player;

bool processInput(GameWorld* GameWorld, Player* player, double dt,
    std::array<bool, K_TOTAL>& key_state, 
    EntityManager* entMan, PhysicsManager* physMan);

bool handleInput(std::array<bool, K_TOTAL> &key_state);

bool updateAll(GameWorld *gw, EntityManager* entMan, PhysicsManager* physMan,
    double t, double dt, std::mt19937 rng);

void render(EntityManager* entMan, PhysicsManager* physMan,
            SDL_Renderer *renderer);
