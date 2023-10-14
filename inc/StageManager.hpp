#include <map>

#include <SDL.h>

#include "Box.hpp"
#include "FlagEnums.hpp"

class Stage;

class StageManager {
public:
    StageManager() {}

    void add_stage(StageID key, Stage* new_stage);
    void run();
private:
    std::map<StageID, Stage*> stages{};
    StageID current{StageID::TITLE_SCREEN};
};
