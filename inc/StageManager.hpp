#include <map>

#include <SDL.h>

#include "Box.hpp"

enum class StageEnum {
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
    virtual int handle_input();
    virtual int update();
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

    void add_stage(Stage new_stage);
    void run();
private:
    std::map<int, Stage> stages;
    StageEnum current_stage{StageEnum::TITLE_SCREEN};
};
