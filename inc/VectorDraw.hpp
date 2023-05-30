#pragma once

#include <vector>

#include <SDL.h>

#include "Colors.hpp"
#include "Vec2d.hpp"

class Box;
struct GameWorld;

void DrawWrapLine(SDL_Renderer *rend, Box screen,
                  double x1, double y1,
                  double x2, double y2);

void ScanFill(GameWorld const* gw, std::vector<Vec2d> poly, SdlColor col, SDL_Renderer* renderer);