#pragma once

#include <array>
#include <string>

#include <SDL.h>

#include "Engine.hpp"
#include "Entity.hpp"
#include "Gun.hpp"
#include "Hyperdrive.hpp"
#include "PhysicsComponent.hpp"
#include "Vec2d.hpp"

class Engine;

class Player : public Entity {
public:
    Player(std::string path, SDL_Renderer* renderer, GameWorld &new_gameWorld);

    Engine engine();
    Gun gun();
    Hyperdrive hyperdrive();
    PhysicsComponent &physicsComponent;

    // void respawn(Vecd2d new_pos, bool reset=true) {};
    void set_turnAmount(double turnSpeed) { turnAmount = turnSpeed; }
    void set_accelerationMag(double power) { accelerationMag = power; }

    void update() override;
    void render(SDL_Renderer *renderer, double progress) override;
private:
    void collide(SDL_Rect &dest, Box screen);
    void updateImage();

    void setPos(int x, int y) { rect.x = x; rect.y = y; }
    void setPos(SDL_Rect newRect) { rect = newRect; }

    Vec2d velocity;
    Vec2d facing_direction;
    Vec2d velocity_direction;
    const double mass;
    double accelerationMag;
    double turnAmount;
    bool isInHyperspace;
};
