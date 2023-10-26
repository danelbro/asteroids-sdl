#include "../inc/GameLoop.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>
#include <vector>

#include <SDL.h>

#include "../inc/FlagEnums.hpp"
#include "../inc/GameWorld.hpp"

namespace GameLoop {
    void process_input(GameWorld& gw, Uint32 windowID,
        std::array<bool, KeyFlag::K_TOTAL>& key_state)
    {
        SDL_Event ev{ };

        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                key_state[KeyFlag::QUIT] = true;

            else if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.windowID == windowID)
                    if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        gw.screen.w = ev.window.data1;
                        gw.screen.h = ev.window.data2;
                    }
            }

            else if (ev.type == SDL_KEYDOWN) {
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key_state[KeyFlag::K_ESCAPE] = true;
                    break;
                case SDLK_LEFT:
                    key_state[KeyFlag::K_LEFT] = true;
                    break;
                case SDLK_RIGHT:
                    key_state[KeyFlag::K_RIGHT] = true;
                    break;
                case SDLK_UP:
                    key_state[KeyFlag::K_UP] = true;
                    break;
                case SDLK_DOWN:
                    key_state[KeyFlag::K_DOWN] = true;
                    break;
                case SDLK_SPACE:
                    key_state[KeyFlag::K_SPACE] = true;
                    break;
                case SDLK_RETURN:
                    key_state[KeyFlag::K_ENTER] = true;
                    break;
                case SDLK_LSHIFT:
                    key_state[KeyFlag::K_LSHIFT] = true;
                    break;
                default:
                    break;
                }
            }
            else if (ev.type == SDL_KEYUP) {
                switch (ev.key.keysym.sym) {
                case SDLK_ESCAPE:
                    key_state[KeyFlag::K_ESCAPE] = false;
                    break;
                case SDLK_LEFT:
                    key_state[KeyFlag::K_LEFT] = false;
                    break;
                case SDLK_RIGHT:
                    key_state[KeyFlag::K_RIGHT] = false;
                    break;
                case SDLK_UP:
                    key_state[KeyFlag::K_UP] = false;
                    break;
                case SDLK_DOWN:
                    key_state[KeyFlag::K_DOWN] = false;
                    break;
                case SDLK_SPACE:
                    key_state[KeyFlag::K_SPACE] = false;
                    break;
                case SDLK_LSHIFT:
                    key_state[KeyFlag::K_LSHIFT] = false;
                    break;
                default:
                    break;
                }
            }
        }
    }
}
