#include "Entity.hpp"
#include "Engine.hpp"
#include "Gun.hpp"
#include "PhysicsComponent.hpp"

class Ship : public Entity {
public:
    Engine engine();
    Gun gun();

    PhysicsComponent *physicsComponent;

protected:
    Ship();
};
