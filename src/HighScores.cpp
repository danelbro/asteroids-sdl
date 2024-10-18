#include "HighScores.hpp"

#include "flags.hpp"

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <utl_Box.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <vector>

HighScores::HighScores(
    utl::Box& screen, uint32_t windowID, utl::Renderer& renderer,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>&, int)
    : utl::Stage{screen, windowID, renderer, STAGE_MAP[STAGE_ID::HIGH_SCORES]}
{}

std::string HighScores::handle_input(double, double,
                                     std::array<bool, utl::KeyFlag::K_TOTAL>&)
{
    return STAGE_MAP[STAGE_ID::HIGH_SCORES];
}

std::string HighScores::update(double, double)
{
    return STAGE_MAP[STAGE_ID::HIGH_SCORES];
}

void HighScores::render(double, double) {}
