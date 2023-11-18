#include "VectorDraw.hpp"

#include <algorithm>
#include <vector>

#include <SDL.h>

#include "Box.hpp"
#include "Colors.hpp"
#include "GameWorld.hpp"
#include "Vec2d.hpp"

namespace utl {
    int wrapCoord(int p, int dim) {
        if (p < 0)
            return dim + p;
        else
            return p % dim;
    }

    void DrawWrapLine(SDL_Renderer *rend, Box screen, double x1, double y1,
                      double x2, double y2) {
        double x{};
        double y{};
        double dy{y2 - y1};
        double dx{x2 - x1};

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
        } else {
            double m{dy / dx};
            double c{y1 - (m * x1)};
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
            } else {
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

    bool PointInPolygon(Vec2d point, std::vector<Vec2d> polygon) {
        // adatpted from https://alienryderflex.com/polygon/
        size_t i, j{polygon.size() - 1};
        bool oddNodes{false};

        for (i = 0; i < polygon.size(); i++) {
            if ((polygon[i].y < point.y && polygon[j].y >= point.y) ||
                (polygon[j].y < point.y && polygon[i].y >= point.y))
              if (polygon[i].x + (point.y - polygon[i].y) /
                                     (polygon[j].y - polygon[i].y) *
                                     (polygon[j].x - polygon[i].x) <
                  point.x)
                oddNodes = !oddNodes;
            j = i;
        }

        return oddNodes;
    }

    void ScanFill(const GameWorld &gw, std::vector<Vec2d> poly, SdlColor col,
                  SDL_Renderer *renderer) {
        // adapted frpm https://alienryderflex.com/polygon_fill/
        SdlColor old{};
        SDL_GetRenderDrawColor(renderer, &old.r, &old.g, &old.b, &old.a);
        SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

        std::vector<double> ys{};
        for (auto p : poly)
            ys.push_back(p.y);
        std::sort(ys.begin(), ys.end());
        double y_min{ys.front()};
        double y_max{ys.back()};

        Vec2d pixel{};

        for (pixel.y = y_min; pixel.y < y_max; pixel.y++) {
            size_t i{}, j{};
            std::vector<double> nodesX;

            j = poly.size() - 1;
            for (i = 0; i < poly.size(); i++) {
              if ((poly[i].y < pixel.y && poly[j].y >= pixel.y) ||
                  (poly[j].y < pixel.y && poly[i].y >= pixel.y))
                nodesX.push_back(poly[i].x +
                                 (pixel.y - poly[i].y) /
                                     (poly[j].y - poly[i].y) *
                                     (poly[j].x - poly[i].x));
              j = i;
            }

            std::sort(nodesX.begin(), nodesX.end());

            for (i = 0; i < nodesX.size(); i += 2) {
              for (pixel.x = nodesX[i]; pixel.x < nodesX.at(i + 1);
                   pixel.x += 1)
                DrawWrapLine(renderer, gw.screen, pixel.x, pixel.y,
                             nodesX.at(i + 1), pixel.y);
            }
        }

        SDL_SetRenderDrawColor(renderer, old.r, old.g, old.b, old.a);
    }


    static void populateNormals(const std::vector<Vec2d>& shape,
                                std::vector<Vec2d>& axes)
    {
        size_t i{};
        for (i = 0; i < shape.size(); ++i) {
            axes.emplace_back(Vec2d{-(shape[i+1 % shape.size()].y - shape[i].y),
                                    shape[i+1 % shape.size()].x - shape[i].x}.normalize());
        }
    }

    bool areColliding_SAT(const std::vector<Vec2d>& shape1,
                          const std::vector<Vec2d>& shape2)
    {
        size_t shape1size = shape1.size();
        size_t shape2size = shape2.size();

        std::vector<Vec2d> axes{};
        axes.reserve(shape1size + shape2size);

        populateNormals(shape1, axes);
        populateNormals(shape2, axes);

        // project shapes onto axes
        for (const auto& axis : axes) {
            double shape1min{ INFINITY }, shape1max{ -INFINITY };
            double shape2min{ INFINITY }, shape2max{ -INFINITY };

            for (const auto& p : shape1) {
                double q = p * axis;
                shape1min = std::min(q, shape1min);
                shape1max = std::max(q, shape1max);
            }

            for (const auto& p : shape2) {
                double q = p * axis;
                shape2min = std::min(q, shape2min);
                shape2max = std::max(q, shape2max);
            }

            if (!(shape2max > shape1min && shape1max > shape2min))
                return false;
        }

        return true;
    }
} // namespace utl
