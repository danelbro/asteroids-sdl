#pragma once

#include <vector>

#include <SDL.h>

#include "Entity.hpp"
#include "FlagEnums.hpp"
#include "Vec2d.hpp"

struct GameWorld;

class PhysicsComponent;

class PhysicsEntity : public Entity
{
public:
	PhysicsEntity(EntityFlag new_type, GameWorld* new_gameWorld, Vec2d pos,
		std::vector<Vec2d> shape, SdlColor color, double scale,
		PhysicsComponent* new_physicsComponent);

	void render(SDL_Renderer* renderer) override;

	PhysicsComponent* physicsComponent;

	std::vector<Vec2d> shape() const { return m_shape; }
	std::vector<Vec2d> transShape() const { return m_transShape; }
	std::vector<Vec2d> fillShape() const { return m_fillShape; }

	bool wayward = true; // for dealing with wayward bullets - find a better way to do this?

protected:
	std::vector<Vec2d> m_transShape;
	std::vector<Vec2d> m_fillShape;

	void update_shapes();
};
