#include "../inc/DrawWrapLine.hpp"

#include <SDL.h>

#include "../inc/Box.hpp"

int wrapCoord(int p, int dim)
{
    if (p < 0)
        return dim + p;
    else
        return p % dim;
}

void DrawWrapLine(SDL_Renderer *rend, Box screen,
                  double x1, double y1,
                  double x2, double y2)
{
    double x{ };
    double y{ };
    double dy{ y2 - y1 };
    double dx{ x2 - x1 };

    if (dx == 0) {
        if (y1 > y2) {
            y = y2;
            y2 = y1;
            y1 = y;
        }
        for (y = y1; y <= y2; ++y)
            SDL_RenderDrawPoint(rend,
                                wrapCoord(static_cast<int>(x1), screen.w),
                                wrapCoord(static_cast<int>(y), screen.h));
    }
    else {
        double m{ dy / dx };
        double c{ y1 - (m * x1) };
        if (-1 <= m && m <= 1) {
            if (x1 > x2) {
                x = x2;
                x2 = x1;
                x1 = x;
            }
            for (x = x1; x <= x2; ++x) {
                y = (m * x) + c;
                SDL_RenderDrawPoint(rend,
                                    wrapCoord(static_cast<int>(x), screen.w),
                                    wrapCoord(static_cast<int>(y), screen.h));
            }
        }
        else {
            if (y1 > y2) {
                y = y2;
                y2 = y1;
                y1 = y;
            }
            for (y = y1; y <= y2; ++y) {
                x = (y - c) / m;
                SDL_RenderDrawPoint(rend,
                                    wrapCoord(static_cast<int>(x), screen.w),
                                    wrapCoord(static_cast<int>(y), screen.h));
            }
        }
    }
}
