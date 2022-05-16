#pragma once

struct Vec2d {
    double magnitude() const;
    double magnitude_squared() const;

    Vec2d normalize();
    Vec2d normalizeInPlace();
    Vec2d update(double new_x, double new_y);
    Vec2d update(Vec2d new_vec);
    Vec2d rotate_deg(double deg);
    Vec2d rotate_rad(double rad);

    double x{ };
    double y{ };
};

// Like a Rect, but without a position
struct Box {
    int w{ };
    int h{ };
};
