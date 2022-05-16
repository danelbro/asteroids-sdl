#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <vector>

#include <SDL.h>

#include "Vec2d.h"

class Player {
public:
    Player();
    ~Player();
    void update(double delta_time);
    void respawn(int respawn_length, int speed, Vec2d new_pos, bool reset);
    void engine_on();
    void engine_off();
    void turn(int turn_dir);
    void hyperspace(int number_of_asteroids);
private:
    void reset(Vec2d pos);
    void calc_velocity(double delta_time);
    void update_image(double delta_time);
};

#endif /* ASTEROIDS_PLAYER_H */
