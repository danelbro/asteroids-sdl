#include "HighScores.hpp"

#include "flags.hpp"

#include <cstdint>
#include <memory>
#include <utl_Box.hpp>
#include <utl_SDLInterface.hpp>
#include <utl_Stage.hpp>
#include <utl_VecGraphPhysEnt.hpp>
#include <vector>

HighScores::HighScores(
    utl::Box& screen, uint32_t windowID, utl::Renderer& renderer,
    const std::vector<std::unique_ptr<utl::VecGraphPhysEnt>>& physEntities,
    int score)
    : utl::Stage{screen, windowID, renderer, STAGE_MAP[STAGE_ID::HIGH_SCORES]}
{}
