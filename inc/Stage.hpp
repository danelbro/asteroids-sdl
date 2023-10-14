#include <SDL.h>

#include "Box.hpp"
#include "FlagEnums.hpp"

class Stage {
public:
    virtual ~Stage() = default;
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;

    virtual void init();
    virtual StageID handle_input();
    virtual StageID update();
    virtual void render();
protected:
    Stage(Box screen, unsigned windowID, SDL_Renderer* renderer)
        : m_screen{ screen }, m_windowID{ windowID }, m_rend{renderer}
        {}
    Box m_screen;
    unsigned m_windowID;
    SDL_Renderer* m_rend;

    bool seen{ false };
};
