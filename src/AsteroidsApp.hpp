#pragma once

#include <cstdint>
#include <string>

#include "Application.hpp"

class AsteroidsApp : public Application
{
public:
    AsteroidsApp(const std::string& title, int screenWidth, int screenHeight, uint32_t windowFlags);
    void trigger_stage_change(const std::string& new_stage) override;
};
