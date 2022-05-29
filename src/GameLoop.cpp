#include "../inc/GameLoop.hpp"

#include <array>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/KeyFlag.hpp"
#include "../inc/Entity.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/Player.hpp"

bool processInput(Player *player, std::array<bool, K_TOTAL> &key_state)
{
    bool isRunning = handleInput(key_state);

    if (key_state[K_UP])
        player->engine.on();
    else if (!key_state[K_UP])
        player->engine.off();

    if (key_state[K_LEFT])
        player->engine.turnLeft();
    if (key_state[K_RIGHT])
        player->engine.turnRight();

    if (key_state[K_SPACE])
        player->gun.fire();

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

void updateAll(std::vector<std::unique_ptr<PhysicsComponent>> &physicsManager,
    double elapsed)
{
    for (auto &physComp : physicsManager)
        physComp->update(elapsed);
}

void render(std::vector<std::shared_ptr<Entity>> &entities,
            SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    for (auto &entity : entities)
        entity->render(renderer);
    SDL_RenderPresent(renderer);
}
