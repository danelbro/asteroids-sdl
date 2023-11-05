#include <random>
#include <vector>

#include "Vec2d.hpp"

namespace utl {
    std::vector<Vec2d> genRandConvexPolygon(int n, double radius,
                                            std::mt19937& rng);
} // namespace utl
