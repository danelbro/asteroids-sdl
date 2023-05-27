#include "../inc/GameLoop.hpp"

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/Entity.hpp"
#include "../inc/EntityManager.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"

bool processInput(GameWorld *gameworld, Player *player, double dt, 
    std::array<bool, K_TOTAL> &key_state, EntityManager *entMan)
{
    bool isRunning = handleInput(key_state);

    if (key_state[K_UP])
        player->engine.on();
    else if (!key_state[K_UP])
        player->engine.off();

    if (key_state[K_LEFT])
        player->engine.turnLeft(dt);
    if (key_state[K_RIGHT])
        player->engine.turnRight(dt);

    if (key_state[K_SPACE])
        if (!player->gun.fired)
            player->gun.fire(gameworld, entMan, player);
    if (!key_state[K_SPACE])
        player->gun.fired = false;

    if (key_state[K_LSHIFT])
        player->hyperdrive.warp();

    return isRunning;
}

bool handleInput(std::array<bool, K_TOTAL> &key_state)
{
    SDL_Event ev;
    bool isRunning{ true };

    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (ev.type == SDL_KEYDOWN) {
            switch (ev.key.keysym.sym) {
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_LEFT:
                key_state[K_LEFT] = true;
                break;
            case SDLK_RIGHT:
                key_state[K_RIGHT] = true;
                break;
            case SDLK_UP:
                key_state[K_UP] = true;
                break;
            case SDLK_DOWN:
                key_state[K_DOWN] = true;
                break;
            case SDLK_SPACE:
                key_state[K_SPACE] = true;
                break;
            case SDLK_LSHIFT:
                key_state[K_LSHIFT] = true;
                break;
            default:
                break;
            }
        }
        else if (ev.type == SDL_KEYUP) {
            switch (ev.key.keysym.sym) {
            case SDLK_LEFT:
                key_state[K_LEFT] = false;
                break;
            case SDLK_RIGHT:
                key_state[K_RIGHT] = false;
                break;
            case SDLK_UP:
                key_state[K_UP] = false;
                break;
            case SDLK_DOWN:
                key_state[K_DOWN] = false;
                break;
            case SDLK_SPACE:
                key_state[K_SPACE] = false;
                break;
            case SDLK_LSHIFT:
                key_state[K_LSHIFT] = false;
                break;
            default:
                break;
            }
        }
    }

    return isRunning;
}

// TODO: remove. Just for suppressing warnings
double animate(double t)
{
    return t+1;
}

void updateAll(std::vector<std::unique_ptr<PhysicsComponent>> &physicsManager,
               double t, double dt)
{
    // TODO: remove. Just for suppressing warnings
    for (int i = 0; i <= 0; ++i)
        animate(t);

    for (auto &physComp : physicsManager)
        physComp->update(dt);
}

void render(std::vector<std::shared_ptr<Entity>> &entities,
            SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    for (auto &entity : entities)
        entity->render(renderer);
    SDL_RenderPresent(renderer);
}
