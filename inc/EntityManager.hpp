#pragma once

// EntityManager class to create, store and destroy Entity-s (non-Physics)

#include <memory>
#include <vector>

#include "Entity.hpp"

class EntityManager {
public:
	EntityManager();

	void clean_up();

	std::vector<std::shared_ptr<Entity>> entities{ };
};