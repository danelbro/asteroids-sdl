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
    PhysicsEntity(const PhysicsEntity&) = default;
    PhysicsEntity& operator=(const PhysicsEntity&) = delete;
    virtual ~PhysicsEntity() = default;

	void render(SDL_Renderer* renderer) override;

	std::vector<Vec2d> shape() const { return m_shape; }
	std::vector<Vec2d> transShape() const { return m_transShape; }
	std::vector<Vec2d> fillShape() const { return m_fillShape; }
    bool isVisible() const { return m_isVisible; }

    void setVisible(bool vis) { m_isVisible = vis }

	PhysicsComponent* physicsComponent;
	bool wayward; // for dealing with wayward bullets - find a better way to do this?

protected:
    PhysicsEntity(EntityFlag new_type, GameWorld& new_gameWorld, Vec2d pos,
                  std::vector<Vec2d> shape, SdlColor color, double scale,
                  PhysicsComponent* new_physicsComponent);
	std::vector<Vec2d> m_transShape;
	std::vector<Vec2d> m_fillShape;
    bool m_isVisible;

	void update_shapes();
};
