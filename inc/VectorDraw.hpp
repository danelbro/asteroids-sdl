#pragma once

#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Vec2d.hpp"

struct Box;
struct GameWorld;

void DrawWrapLine(SDL_Renderer *rend, Box screen,
                  double x1, double y1,
                  double x2, double y2);

bool PointInPolygon(Vec2d point, std::vector<Vec2d> polygon);

void ScanFill(GameWorld& gw, std::vector<Vec2d> poly, 
    SdlColor col, SDL_Renderer* renderer);
