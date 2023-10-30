#pragma once

struct Vec2d {
    double magnitude() const;
    double magnitude_squared() const;
    double angle() const;
    double angleDeg() const;

    Vec2d operator*(double x);
    // dot product
    double operator*(Vec2d otherVec);

    Vec2d operator/(double x);

    Vec2d operator+(Vec2d otherVec);

    Vec2d operator+=(Vec2d otherVec);

    Vec2d operator-();
    Vec2d operator-(Vec2d otherVec);

    Vec2d normalize();
    Vec2d normalizeInPlace();
    Vec2d update(double new_x, double new_y);
    Vec2d update(Vec2d new_vec);
    Vec2d rotate_rad(double rad);
    void rotate_rad_ip(double rad);
    Vec2d rotate_deg(double deg);
    void rotate_deg_ip(double deg);

    double x{ };
    double y{ };
};
