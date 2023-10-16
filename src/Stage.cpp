#include "../inc/Stage.hpp"

#include "../inc/FlagEnums.hpp"

Stage::~Stage() {}

StageID Stage::handle_input(double, double,
                            std::array<bool, static_cast<size_t>(KeyFlag::K_TOTAL)>&)
{
    return StageID::STAGES_TOTAL;
}

StageID Stage::update(double, double)
{
    return StageID::STAGES_TOTAL;
}

void Stage::render(double, double) {}
