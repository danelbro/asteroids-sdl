#ifndef ASTEROIDS_VEC2D_H
#define ASTEROIDS_VEC2D_H

class Vec2d {
public:
    double x;
    double y;
    double magnitude();
    double magnitude_squared();
    Vec2d normalize();
    void update(Vec2d new_vec);
    Vec2d rotate(double rad);
}

#endif /* ASTEROIDS_VEC2D_H */
