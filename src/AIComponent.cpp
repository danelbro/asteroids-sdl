#include "AIComponent.hpp"

#include "Enemy.hpp"
#include "Player.hpp"

AIComponent::AIComponent(Enemy& new_owner)
    : owner{ new_owner }
{}

void AIComponent::update(double, double, Player*)
{

}
