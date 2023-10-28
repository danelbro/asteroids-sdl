#pragma once

#include <array>

#include <SDL.h>

#include "Box.hpp"
#include "FlagEnums.hpp"

class Stage {
public:
    Stage(const Stage&) = default;
    Stage& operator=(const Stage&) = default;
    virtual ~Stage() = default;

    virtual StageID handle_input(double t, double dt,
                                 std::array<bool,
                                 static_cast<size_t>(
                                     KeyFlag::K_TOTAL)>& key_state) = 0;
    virtual StageID update(double t, double dt) = 0;
    virtual void render(double t, double dt) = 0;

    Box screen() const { return m_screen; }
    unsigned windowID() const { return m_windowID; }
    SDL_Renderer* renderer() const { return m_rend; }
    StageID ID() const { return m_ID; }
protected:
    Stage(Box screen, unsigned windowID, SDL_Renderer* renderer, StageID id)
        : m_screen{ screen }, m_windowID{ windowID }, m_rend{renderer},
          m_ID{ id }
        {}
private:
    Box m_screen;
    unsigned m_windowID;
    SDL_Renderer* m_rend;
    StageID m_ID;
};
