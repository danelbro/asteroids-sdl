#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H

#include <vector>

#include <SDL.h>

enum dir_flag {
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    DIR_TOTAL
};

// Quit the game on certain inputs
void handle_input(bool &running, std::vector<bool> &key_state);

#endif
