#pragma once

#include <vector>

#include <SDL.h>

#include "Entity.hpp"
#include "Vec2d.hpp"

class GameWorld;
class PhysicsComponent;

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(GameWorld* new_gameWorld, Vec2d pos,
		std::vector<Vec2d> shape, SdlColor color, double scale,
		PhysicsComponent* new_physicsComponent);

	void render(SDL_Renderer* renderer) override;

	PhysicsComponent* physicsComponent;
};