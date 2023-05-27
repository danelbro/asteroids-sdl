#include "../inc/EntityManager.hpp"

EntityManager::EntityManager()
	: entities{ }
{}

void EntityManager::clean_up()
{
	for (size_t i{ 0 }; i < entities.size(); i++)
		if (entities[i]->kill_it())
			entities.erase(entities.begin() + i);
}