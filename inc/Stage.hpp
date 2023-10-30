#pragma once

#include <array>

#include <SDL.h>

#include "Box.hpp"
#include "utility.hpp"

class Stage {
public:
    Stage(const Stage&) = default;
    Stage& operator=(const Stage&) = default;
    virtual ~Stage() = default;

    virtual utl::StageID handle_input(double t, double dt,
        std::array<bool, utl::KeyFlag::K_TOTAL>& key_state) = 0;
    virtual utl::StageID update(double t, double dt) = 0;
    virtual void render(double t, double dt) = 0;

    Box screen() const { return m_screen; }
    unsigned windowID() const { return m_windowID; }
    SDL_Renderer* renderer() const { return m_rend; }
    utl::StageID ID() const { return m_ID; }
protected:
    Stage(Box screen, unsigned windowID, SDL_Renderer* renderer,
          utl::StageID id)
        : m_screen{ screen }, m_windowID{ windowID }, m_rend{renderer},
          m_ID{ id }
        {}
private:
    Box m_screen;
    unsigned m_windowID;
    SDL_Renderer* m_rend;
    utl::StageID m_ID;
};
