#include "../inc/Vec2d.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

double Vec2d::magnitude() const
{
    return std::sqrt(magnitude_squared());
}

double Vec2d::magnitude_squared() const
{
    return x * x + y * y;
}

double Vec2d::angle() const
{
    return M_PI - atan2(x, y);
}

double Vec2d::angleDeg() const
{
    return angle() * 180 / M_PI;
}

Vec2d Vec2d::normalizeInPlace()
{
    auto mag = magnitude();
    if (mag != 0) {
        x /= mag;
        y /= mag;
    }
    return *this;
};

Vec2d Vec2d::normalize()
{
    auto mag = magnitude();
    if (mag == 0) {
        return *this;
    }
    return Vec2d{ x / mag, y / mag };
};

Vec2d Vec2d::update(double new_x, double new_y)
{
    x = new_x;
    y = new_y;

    return *this;
}

Vec2d Vec2d::update(Vec2d new_vec)
{
    return update(new_vec.x, new_vec.y);
}

Vec2d Vec2d::rotate_rad(double rad)
{
    double new_x = (x * std::cos(rad)) - (y * std::sin(rad));
    double new_y = (x * std::sin(rad)) + (y * std::cos(rad));

    return Vec2d{ new_x, new_y };
}

void Vec2d::rotate_rad_ip(double rad)
{
    x = (x * std::cos(rad)) - (y * std::sin(rad));
    y = (x * std::sin(rad)) + (y * std::cos(rad));
}

Vec2d Vec2d::rotate_deg(double deg)
{
    return rotate_rad(deg * (M_PI / 180.0));
}

void Vec2d::rotate_deg_ip(double deg)
{
    rotate_rad_ip(deg * (M_PI / 180.0));
}

Vec2d Vec2d::operator*(double n)
{
    return Vec2d{ x * n, y * n };
}
double Vec2d::operator*(Vec2d otherVec)
{
    return x * otherVec.x + y * otherVec.y;
}

Vec2d Vec2d::operator/(double n)
{
    return Vec2d{ x / n, y / n };
}

Vec2d Vec2d::operator+(Vec2d otherVec)
{
    return Vec2d{ x + otherVec.x, y + otherVec.y };
}

Vec2d Vec2d::operator+=(Vec2d otherVec)
{
    *this = *this + otherVec;
    return *this;
}

Vec2d Vec2d::operator-()
{
    return Vec2d{ *this * -1 };
}

Vec2d Vec2d::operator-(Vec2d otherVec)
{
    return Vec2d{ x - otherVec.x, y - otherVec.y };
}
