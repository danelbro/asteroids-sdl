#pragma once

#include "utl_Application.hpp"

#include <cstdint>
#include <string>

class AsteroidsApp : public utl::Application {
public:
    AsteroidsApp(const std::string& title, int screenWidth, int screenHeight,
                 uint32_t windowFlags);
    void trigger_stage_change(const std::string& new_stage) override;
};
