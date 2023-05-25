#pragma once

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Hyperdrive.hpp"
#include "Ship.hpp"
#include "Vec2d.hpp"

struct GameWorld;
class PhysicsComponent;

class Player : public Ship {
public:
    Player(GameWorld *new_gameWorld, Vec2d pos,
           std::vector<Vec2d> shape, SdlColor color, double scale,
           double power, double turnSpeed,
           double shotPower,
           PhysicsComponent *new_physicsComponent,
           double warpTimer, int new_lives);

    Hyperdrive hyperdrive;

    void respawn(Vec2d new_pos, bool reset=true);

    void render(SDL_Renderer *renderer) override;
private:
    bool isVisible;
    bool isControllable;
    int lives;
};
