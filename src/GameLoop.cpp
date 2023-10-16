#include "../inc/GameLoop.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/Entity.hpp"
#include "../inc/EntityManager.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/PhysicsComponent.hpp"
#include "../inc/PhysicsManager.hpp"
#include "../inc/Player.hpp"
#include "../inc/ScoreManager.hpp"

namespace GameLoop {
    void process_input(GameWorld* gw, Uint32 windowID, std::array<bool,
                     static_cast<size_t>(KeyFlag::K_TOTAL)>& key_state)
    {
        SDL_Event ev{ };

        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                key_state[static_cast<size_t>(KeyFlag::QUIT)] = true;

            else if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.windowID == windowID)
                    if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        gw->screen.w = ev.window.data1;
                        gw->screen.h = ev.window.data2;
                    }
            }

            else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key_state[static_cast<size_t>(KeyFlag::K_ESCAPE)] = true;
                    break;
                case SDLK_LEFT:
                    key_state[static_cast<size_t>(KeyFlag::K_LEFT)] = true;
                    break;
                case SDLK_RIGHT:
                    key_state[static_cast<size_t>(KeyFlag::K_RIGHT)] = true;
                    break;
                case SDLK_UP:
                    key_state[static_cast<size_t>(KeyFlag::K_UP)] = true;
                    break;
                case SDLK_DOWN:
                    key_state[static_cast<size_t>(KeyFlag::K_DOWN)] = true;
                    break;
                case SDLK_SPACE:
                    key_state[static_cast<size_t>(KeyFlag::K_SPACE)] = true;
                    break;
                case SDLK_LSHIFT:
                    key_state[static_cast<size_t>(KeyFlag::K_LSHIFT)] = true;
                    break;
                default:
                    break;
                }
            }
            else if (ev.type == SDL_KEYUP)
                std::fill(key_state.begin(), key_state.end(), false);
        }

    }

}
