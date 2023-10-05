#include <map>

#include <SDL.h>

#include "Box.hpp"

enum class StageID {
    TITLE_SCREEN,
    PLAYING,
    HIGH_SCORES,
    STAGES_TOTAL
};

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
private:
    Box m_screen;
    unsigned m_windowID;
    SDL_Renderer* m_rend;

    bool seen{ false };
};

class StageManager {
public:
    StageManager();

    void add_stage(StageID key, Stage& new_stage);
    void run();
private:
    std::map<StageID, Stage> stages;
    StageID current{StageID::TITLE_SCREEN};
};
