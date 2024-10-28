#pragma once

#include <string>
#include <utl_Application.hpp>
#include <utl_random.hpp>

class AsteroidsApp : public utl::Application {
public:
    AsteroidsApp();
    AsteroidsApp(const std::string& title);
    AsteroidsApp(const std::string& title, int screenWidth, int screenHeight);
    ~AsteroidsApp() override;
    void trigger_stage_change(const std::string& new_stage) override;

private:
    void init();

    utl::RNG m_rng;
};
