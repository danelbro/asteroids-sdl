#include "../inc/VectorDraw.hpp"

#include <algorithm>
#include <vector>

#include <SDL.h>

#include "../inc/Box.hpp"
#include "../inc/GameWorld.hpp"
#include "../inc/Vec2d.hpp"

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

bool PointInPolygon(Vec2d point, std::vector<Vec2d> polygon)
{
    // adatpted from https://alienryderflex.com/polygon/
    size_t i, j{ polygon.size() - 1 };
    bool oddNodes{ false };

    for (i = 0; i < polygon.size(); i++) {
        if (polygon[i].y < point.y && polygon[j].y >= point.y 
            || polygon[j].y < point.y && polygon[i].y >= point.y)
                if (polygon[i].x + (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) * (polygon[j].x - polygon[i].x) < point.x)
                    oddNodes = !oddNodes;
        j = i;
    }

    return oddNodes;
}

void ScanFill(GameWorld const* gw, std::vector<Vec2d> poly, SdlColor col, SDL_Renderer* renderer)
{
    // adapted form https://alienryderflex.com/polygon_fill/
    SdlColor old{};
    SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.b, &old.a);
    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

    std::vector<double> ys{};
    for (auto p : poly)
        ys.push_back(p.y);
    std::sort(ys.begin(), ys.end());
    double y_min{ ys.front() };
    double y_max{ ys.back() };

    Vec2d pixel{};

    for (pixel.y = y_min; pixel.y < y_max; pixel.y++) {
        size_t i{}, j{};
        std::vector<double> nodesX;
        
        j = poly.size() - 1;
        for (i = 0; i < poly.size(); i++) {
            if (poly.at(i).y < pixel.y && poly.at(j).y >= pixel.y
                || poly.at(j).y < pixel.y && poly.at(i).y >= pixel.y)
                nodesX.push_back(
                    poly.at(i).x
                    + (pixel.y - poly.at(i).y)
                    / (poly.at(j).y - poly.at(i).y)
                    * (poly.at(j).x - poly.at(i).x));
            j = i;
        }


        std::sort(nodesX.begin(), nodesX.end());

        for (i = 0; i < nodesX.size(); i += 2) {
            for (pixel.x = nodesX.at(i); pixel.x < nodesX.at(i + 1); pixel.x += 1)
                DrawWrapLine(renderer, gw->screen, pixel.x, pixel.y, nodesX.at(i + 1), pixel.y);
        }
    }

    SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
}
