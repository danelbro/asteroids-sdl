#include "../inc/AIComponent.hpp"

#include "../inc/Enemy.hpp"

AIComponent::AIComponent(Enemy& new_owner)
    : owner{ new_owner }
{}

void AIComponent::update(double, double, Player*)
{

}
