#pragma once

#include <cstdint>
#include <string>

#include "Application.hpp"

class AsteroidsApp : public Application
{
public:
    AsteroidsApp(const std::string& title, int screenWidth, int screenHeight,
                 uint32_t windowFlags, uint32_t renderFlags);
    void trigger_stage_change(utl::StageID new_stage) override;
};
