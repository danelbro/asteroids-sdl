#pragma once

#include <array>

#include <SDL.h>

#include "Box.hpp"
#include "FlagEnums.hpp"

class Stage {
public:
    virtual ~Stage();
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;

    virtual StageID handle_input(double t, double dt,
                                 std::array<bool,
                                 static_cast<size_t>(KeyFlag::K_TOTAL)>& key_state);
    virtual StageID update(double t, double dt);
    virtual void render(double t, double dt);

    Box screen() const { return m_screen; }
    unsigned windowID() const { return m_windowID; }
    SDL_Renderer* renderer() const { return m_rend; }
protected:
    Stage(Box screen, unsigned windowID, SDL_Renderer* renderer)
        : m_screen{ screen }, m_windowID{ windowID }, m_rend{renderer}
        {}
private:
    Box m_screen;
    unsigned m_windowID;
    SDL_Renderer* m_rend;

    bool seen{ false };
};
