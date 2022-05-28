#pragma once

#include <SDL.h>

class Box;

void DrawWrapLine(SDL_Renderer *rend, Box screen,
                  double x1, double y1,
                  double x2, double y2);
