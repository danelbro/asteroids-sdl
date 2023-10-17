#include "../inc/AIComponent.hpp"

#include "../inc/Enemy.hpp"

AIComponent::AIComponent()
    : owner{ nullptr }
{}

void AIComponent::update(double t, double dt, Player* plr)
{

}


void AIComponent::setOwner(Enemy* new_owner)
{
    if (new_owner)
        owner = new_owner;
}