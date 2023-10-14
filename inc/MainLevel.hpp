#include <chrono>
#include <random>

#include <SDL.h>

#include "Box.hpp"
#include "EntityManager.hpp"
#include "GameWorld.hpp"
#include "PhysicsManager.hpp"
#include "ScoreManager.hpp"
#include "Stage.hpp"

class MainLevel : public Stage {
public:
    MainLevel(Box screen, Uint32 windowID, SDL_Renderer* renderer)
        : Stage{screen, windowID, renderer}, gameWorld{}, entityManager{},
          physicsManager{}
        {
            std::random_device randDev;
            rng = std::mt19937{randDev()};
            std::mt19937::result_type seed_val{ static_cast<unsigned long>(std::time(NULL)) };
            rng.seed(seed_val);
        }

    void init();
    StageID handle_input();
    StageID update();
    void render();
private:
    GameWorld gameWorld;
    EntityManager entityManager;
    PhysicsManager physicsManager;
    ScoreManager scoreManager;
    std::mt19937 rng;
};
