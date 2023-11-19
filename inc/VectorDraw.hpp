#pragma once

#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Vec2d.hpp"

struct Box;
struct GameWorld;

namespace utl {
    void wrap(Vec2d& pos, const Box& bounds);

    void DrawWrapLine(SDL_Renderer *rend, const Box& screen,
                      double x1, double y1,
                      double x2, double y2);

    bool PointInPolygon(const Vec2d& point, const std::vector<Vec2d>& polygon);

    void ScanFill(const GameWorld& gw, const std::vector<Vec2d>& poly,
    const SdlColor& col, SDL_Renderer* renderer);

    bool areColliding_SAT(const std::vector<Vec2d>& shape1,
                          const std::vector<Vec2d>& shape2);
}
